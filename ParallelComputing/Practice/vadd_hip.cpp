#include "hip/hip_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define HIP_ASSERT(x) (assert((x)==hipSuccess))

// HIP kernel. Each thread takes care of one element of c
__global__ void vecAdd(double *a, double *b, double *c, int n)
{
    // Get our global thread ID
    int id = blockIdx.x*blockDim.x+threadIdx.x;
 
    // Make sure we do not go out of bounds
    if (id < n)
        c[id] = a[id] + b[id];
}
 
int main( int argc, char* argv[] )
{
    // Size of vectors
    int n = 100000;
 
    // Host input vectors
    double *h_a;
    double *h_b;
    //Host output vector
    double *h_c;
    //Host output vector for verification
    double *h_verify_c;
 
    // Device input vectors
    double *d_a;
    double *d_b;
    //Device output vector
    double *d_c;
 
    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(double);
 
    // Allocate memory for each vector on host
    h_a = (double*)malloc(bytes);
    h_b = (double*)malloc(bytes);
    h_c = (double*)malloc(bytes);
    h_verify_c = (double*)malloc(bytes);

   printf("Finished allocating vectors on the CPU\n");     
    // Allocate memory for each vector on GPU
   HIP_ASSERT(hipMalloc(&d_a, bytes));
   HIP_ASSERT(hipMalloc(&d_b, bytes));
   HIP_ASSERT(hipMalloc(&d_c, bytes));
 
   printf("Finished allocating vectors on the GPU\n");

    int i;
    // Initialize vectors on host
    for( i = 0; i < n; i++ ) {
        h_a[i] = i;
        h_b[i] = i;
    }


 
    // Copy host vectors to device
    HIP_ASSERT(hipMemcpy( d_a, h_a, bytes, hipMemcpyHostToDevice));
    HIP_ASSERT(hipMemcpy(d_b, h_b, bytes, hipMemcpyHostToDevice));
 
    printf("Finished copying vectors to the GPU\n");

    int blockSize, gridSize;
 
    // Number of threads in each thread block
    blockSize = 1024;
 
    // Number of thread blocks in grid
    gridSize = (int)ceil((float)n/blockSize);
 
    printf("Launching the  kernel on the GPU\n");
    // Execute the kernel
    hipLaunchKernelGGL(vecAdd, dim3(gridSize), dim3(blockSize), 0, 0, d_a, d_b, d_c, n);
    hipDeviceSynchronize( );
    printf("Finished executing kernel\n");
    // Copy array back to host
   HIP_ASSERT(hipMemcpy( h_c, d_c, bytes, hipMemcpyDeviceToHost));
   printf("Finished copying the output vector from the GPU to the CPU\n");

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

    printf("Printing few elements from the output vector\n");

    for(i=0; i < 20; i++)
    {
     printf("Output[%d]:%f\n",i, h_c[i]);	    
    }

    printf("Releasing GPU memory\n");
     
    // Release device memory
    HIP_ASSERT(hipFree(d_a));
    HIP_ASSERT(hipFree(d_b));
    HIP_ASSERT(hipFree(d_c));
 
    // Release host memory
    printf("Releasing CPU memory\n");
    free(h_a);
    free(h_b);
    free(h_c);
 
    return 0;
}
