# Vector Addition

To show how using GPU can optimize computationally intensive problem, we will be utilizing Vector Addition as our example.
We will be walking through main steps in the code. 

The first thing we see are headers and macros to allow runtime calls. HIP_ASSERT is used to check if runtime API calls fail 
```c++
#include "hip/hip_runtime.h"                                                    
#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <math.h>                                                               
                                                                                
                                                                                
#define HIP_ASSERT(x) (assert((x)==hipSuccess))
```
Next step is to allocate memory on the GPU using runtime call "hipMalloc"

```c++
// e.g. allocate the variable d_a and reserve a total of “bytes” storage for i
HIP_ASSERT(hipMalloc(&d_a, bytes));                                          
HIP_ASSERT(hipMalloc(&d_b, bytes));                                          
HIP_ASSERT(hipMalloc(&d_c, bytes));  
```

Next, we want to transfer the initialized data to the GPU using the API call "hipMemcpy"
```c++
// copy a total of “bytes” bytes from the host array “h_a” to the device array “d_a”
HIP_ASSERT(hipMemcpy( d_a, h_a, bytes, hipMemcpyHostToDevice));             
HIP_ASSERT(hipMemcpy(d_b, h_b, bytes, hipMemcpyHostToDevice));
```

Then, we lanch the kernel where it forms a grid of threads (gridSize x blockSize)
and hipDeviceSynchronize ensures that the computation on the GPU is complete
```c++
hipLaunchKernelGGL(vecAdd, dim3(gridSize), dim3(blockSize), 0, 0, d_a, d_b, d_c, n);
hipDeviceSynchronize( ); 
```

We copy array back from GPU to CPU (host) and store it in h_c
```c++
HIP_ASSERT(hipMemcpy( h_c, d_c, bytes, hipMemcpyDeviceToHost)); 
```

To verify the result of the kernel, it is compared to CPU counterpart
```c++
//Compute for CPU                                                            
for(i=0; i <n; i++)                                                          
{                                                                            
   h_verify_c[i] = h_a[i] + h_b[i];                                            
}                                                                            


//Verfiy results                                                            
for(i=0; i <n; i++)                                                         
{                                                                           
   if (abs(h_verify_c[i] - h_c[i]) > 1e-5)                                     
   {                                                                          
      printf("Error at position i %d, Expected: %f, Found: %f \n", i, h_c[i], d_c[i]);
   }                                                                          
}
```

Lastly, it is important to free the memory once the work is done
```c++                                                                          
// Release device memory                                                    
HIP_ASSERT(hipFree(d_a));                                                   
HIP_ASSERT(hipFree(d_b));                                                   
HIP_ASSERT(hipFree(d_c));
``` 

To break this down we can split it up into the following parts.

1st Line
 - `#pragma omp` starts the OpenMP compiler directive
 - `target data` creates a data environment for the GPU (target)
 - `map(to: A[0:hA*wA], B[0:wA*wB])` says the `A` and `B` will only be read from on the GPU
 - `map(from: C[0:hA*wB])` says that `C` will only be written to on the GPU

 This map clause helps reduce data transfers between the CPU and GPU by saying what is being read from and what is being written to.

2nd Line
 - `#pragma omp` starts the OpenMP compiler directive
 - `target` says to offload the work to the GPU
 - `teams distribute` creates a league of teams to distribute threads over
 - `parallel for` says to create a team of OpenMP threads to parallelize the following for loop
 - `collapse(2)` says how many loops to parallelize
 - `schedule(static)` maps threads to iterations in a round robin order. This means the access to memory are more GPU friendly than `schedule(dynamic)`. Check out this [Stack Overflow question](https://stackoverflow.com/questions/10850155/whats-the-difference-between-static-and-dynamic-schedule-in-openmp) for more details.

We can add this to our code to easily leverage the GPU.

```c++
// C = AB
void matrixMultiply(float* C, float* A, unsigned int hA, unsigned int wA, float*B, unsigned int wB) {
    #pragma omp target data map(to: A[0:hA*wA], B[0:wA*wB]) map(from: C[0:hA*wB])
    #pragma omp target teams distribute parallel for collapse(2) schedule(static)
    
    for(unsigned int i=0;i < hA;i++) {
        for(unsigned int j=0;j < wB;j++) {
            float sum = 0;
            for(unsigned int k=0;k < wA;k++) {
                sum += A[i * wA + k]*B[k * wB + j];
            }
            C[i * wB + j] = sum;
        }
    }
}
```

You can test this out by compiling with hipcc (compiler for HIP) or Make, produce executable called vadd_hip
```
hipcc vadd_hip.cpp -o vadd_hip
```
WARNING: This method of compilation has not been tested and may need to have arguments added/adjusted.

## References 
[AMD developer HIP](https://developer.amd.com/wp-content/resources/ROCm%20Learning%20Centre/chapter3/HIP-Coding-3.pdf).

