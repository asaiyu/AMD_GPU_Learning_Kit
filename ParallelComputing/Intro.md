# Parallel Computing and Multi-Thread Execution


## What is Parallel Computing and Multithreading?
CPUs and GPUs are designed very differently. Even though most modern CPU designs include SIMD instructions to improve the performance of multimedia use, GPUs have capability of having multiple operations (calculations or executions) of processes are carried out simultaneously. This concept of parallel computing brings out another topic: multithreading.

## Thread (Work items) vs. Warps (Wavefront) vs. Block  
Thread are chain of instructions running on a core processor. There can be as many as 32 threads in warps (64 in wavefront) running on same core. 
Warp is a group of threads. 
Block is a group of threads consisting of many warps running on same streaming multiprocessor (SM).

## Memory Model -- What is a grid and a block?
As mentioned earlier,  parallel code -- in the kernel -- is launched and executed on a device (GPU) by many threads. 
These threads are grouped into blocks, which are grouped into grids. Think of a grid as an array of threads, where each thread is an index.

Thread blocks have a feature of scalable cooperation where threads within a block cooperate through shared memory, atomic operations and barrier synchronization. Key point to note that threads in different blocks do not interact; therefore, the GPU will execute an instruction for all threads in the same block before moving to next instruction.  It is better to avoid diverging within a block (thread divergence) 

    Divergence:                        without divergence:
    If (threadId > 2) {...}            if (threadId / block_size > 2) {...}
    Else {...}                         else {...}

## Memory Coalescing 
Another concept to point out is memory coalescing transaction -- all of the threads in a warp access global memory at the same time. 
If a kernel iterates through a row, the access to global memory are much less efficient than as such though a column. In that case, we can use shared memory to enable memory coalescing.

## Atomic Operation
It makes sure that that one and only thread has access to a piece of memory while an operation completes. 
During an atomic operation, another processor cannot read and write until the atomic operation has finished -- like a lock and protection to avoid any data errors.

In shared memory, it is used to prevent race conditions between different threads within the same thread block.
In global memory, it is used to prevent race conditions between two different threads regardless of which thread block they are in.


## Practice Problems / Questions
- [Review questions on this topic](Practice/Questions.md)
- [Practice](Practice/Examples.md)

