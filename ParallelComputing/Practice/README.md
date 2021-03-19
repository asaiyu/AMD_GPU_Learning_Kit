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

You can test this out by compiling with hipcc (compiler for HIP) or Make, produce executable called vadd_hip
```
hipcc vadd_hip.cpp -o vadd_hip
```

## References 
[AMD developer HIP](https://developer.amd.com/wp-content/resources/ROCm%20Learning%20Centre/chapter3/HIP-Coding-3.pdf).

