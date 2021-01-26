# OpenMP Matrix Multiplication

To show how we can parallelize our code with OpenMP we will take a naive implementation of matrix multiplication and parallelize it.

```c++
// C = AB
void matrixMultiply(float* C, float* A, unsigned int hA, unsigned int wA, float*B, unsigned int wB) {
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

This algorithm follows the definition of matrix multiplication as described at [Wikipedia](https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm#Iterative_algorithm).

The first and second loops in this algorithm do not have data dependence between iterations and can be parallelized. If we split this up between "workers", we would want each worker to run the following code.

```c++
// Worker Code
float sum = 0;
for(unsigned int k=0;k < wA;k++) {
    sum += A[i * wA + k]*B[k * wB + j];
}
C[i * wB + j] = sum;
```

Thanks to OpenMP we do not have to manage threads or change any code. We can parallelize it using

```c++
#pragma omp target data map(to: A[0:hA*wA], B[0:wA*wB]) map(from: C[0:hA*wB])
```

and

```c++
#pragma omp target teams distribute parallel for collapse(2) schedule(static)
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

We can adds this to our code to easily leverage the GPU.

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

You can test this out with the code in this directory. Make sure to have AOMP installed then run `make`. Try removing the `#pragma` lines and comparing the execution time.

If you try to compile it manually make sure to use `-fopenmp` and specify the correct target with `-fopenmp-targets=` and `-Xopenmp-target=`

## Verifying GPU utilization

An easy way to verify if your GPU is actually being utilized is to run `watch -n .5 rocm-smi` in another terminal. When you run the executable GPU utilization should increase.

## Notes On Performance
This implementation for matrix multiplication is not cache friendly. If we assume that each row is the same size as a cache line we can see that for each iteration of the k loop each access to B would hit a new cache line. This means that this code does not take full advantage of previously cached data. A better implementation is left as an exercise for the reader :)

Wikipedia has a great article for [matrix multiplication algorithms](https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm#Cache_behavior).
