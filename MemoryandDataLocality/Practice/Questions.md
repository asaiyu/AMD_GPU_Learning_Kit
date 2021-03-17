<details>
<summary>Why should we avoid accessing global memory?</summary>
<br>
Accessing global memory is slow, and can bottleneck programs that would otherwise run very efficiently.
</details>

<details>
<summary>What types of memory are in a GPU?</summary>
<br>
GPUs contain registers, shared memory, and global memory.
</details>

<details>
<summary>What are registers? Why should I use them?</summary>
<br>
Registers are memory that are private to a thread, and allow caching of data within a thread. Registers take fewer instructions to access compared to global memory, and require less energy to access. It can also be helpful to have variables that are private to a given thread.
</details>

<details>
<summary>What is shared memory?</summary>
<br>
Shared memory is a cache that all threads in a thread block can access.
</details>

<details>
<summary>What are tiles?</summary>
<br>
Tiles are subsets of data. Tiling is used to improve memory locality in a nested loop by adjusting the iteration order.
</details>

<details>
<summary>Are there issues with tiling? Can we address them?</summary>
<br>
Tiling can lead to attempts to load elements that do not exist, causing issues. To address this, there are multiple boundary checks we can use, including checking an element's indexes.
</details>
