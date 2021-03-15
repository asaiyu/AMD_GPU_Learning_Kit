# Memory and Data Locality
Note: Memory and data locality is very similar between NVIDIA and AMD GPUs. Though this section will give a brief overview of the topic, it's worth learning more from the sources below.


## Memory Access Efficiency
One of the most important aspects of a GPU is its efficiency in memory access. On most high-end devices today, global memory bandwidth is around 1 TB/s. Because single-precision floating-point values are around 4 bytes, this means at most, 250 giga single-precision operations can be expected to run in a second. Any program whose execution speed is limited by the amount of memory access that can occur in a second is a memory-bound program.

In order to achieve higher than 250 GFLOPS (giga floating-point operations per second), GPUs reduce the number of times a program needs to access global memory.


## Memory Types
GPUs contain many different types of memory in order to help programmers achieve fewer global memory accesses. There are registers and shared memory, which are on-chip memories. Variables in these types of memory are easily and quickly accessed. Registers can only be accessed by its own threads, as each register is allocated to an individual thread. Shared memory is stored in thread blocks, where all threads in a block can access this memory.

One big reason to use registers when possible is that accessing registers takes fewer instructions than accessing global memory. However, if an operand value is in global memory, a processor would need to perform a memory load operation.

Another reason to use registers is that in modern computers, the energy needed to access a register file is at least an order of magnitude lower than the energy needed to access a value from global memory.

The biggest thing to keep in mind is that variables in shared memory can be accessed by all threads in a block, whereas variables in registers are tied to their thread and cannot be accessed elsewhere.


## Tiling
We now know that global memory is large and useful, but slow, whereas shared memory is small but fast. One way to split up this data is by creating subsets which are called tiles, where each tile is in shared memory.

Tiling is used mainly to improve memory locality within a nested loop. To do this, it changes the iteration order of the loop. In order to achieve tiling, the number of loops is doubled and the amount of parallelism available in the outer loops is reduced.

Tiling is used in all GPU programming, not just on AMD GPUs. For more information, see the article on Tiling in the Resources section.


## Boundary Checks
One issue when tiling can be that you attempt to load elements that do not exist. Accessing nonexistant elements can lead to work being done on incorrect elements in a matrix, or can produce incorrect values. On some machines, attempting to access outside the allocated area for an array can raise an error and cause the program to completely abort. In any case, we want to avoid this.

This problem is solved using boundary checks. When a thread wants to load an input tile element, it should also check the element for validity (simply by checking the x and y indexes). If this condition is not met, the thread should not load the element, and a value of 0.0 should be placed in this shared memory location. We choose 0.0 because this will not cause harm when being used in calculations. We should also check that the current thread is actually responsible for calculating a given element in a matrix. The way you could test this is by checking if Row < Width and Col < Width.


## Differences between AMD and NVIDIA
As mentioned earlier, most information you can find online or elsewhere involving how memory and data locality works on NVIDIA GPUs also applies to AMD GPUs. There are a few differences in their implementations, but from a programmer's point of view, the concepts are identical.


## Practice Problems / Questions
- [Review questions on this topic](Practice/Questions.md)
- [Practice](Practice/Examples.md)


## Resources / References
- [Parallel Programming - Tiling](https://nichijou.co/cuda7-tiling)
- [HIPIFY GitHub Repo](https://github.com/ROCm-Developer-Tools/HIPIFY)
- [Architecture Comparison between NVIDIA and ATI GPUs](https://www.ece.lsu.edu/lpeng/papers/iiswc11.pdf)
- [NVIDIA Accelerated Computing Teaching Kit](https://developer.nvidia.com/teaching-kits)
