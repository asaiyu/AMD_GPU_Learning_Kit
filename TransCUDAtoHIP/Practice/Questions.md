<details>
<summary>What is CUDA?</summary>
<br>
CUDA is a development platform for GPU computing, used mainly for Nvidia GPUs.
</details>

<details>
<summary>What is the difference between CUDA and HIP?</summary>
<br>
While both CUDA and HIP are used to write GPU-optimized software, CUDA is only supported within its proprietary hardware environment, while HIP is universal.
</details>

<details>
<summary>Why should CUDA code be translated to HIP?</summary>
<br>
Translating CUDA code to HIP allows the code to run on more platforms, breaking it out of its vendor lock-in.
</details>

<details>
<summary>What tools are available to transltae CUDA to HIP?</summary>
<br>
  <ul>
    <li>hipify-perl</li>
    <li>hipify-clang</li>
  </ul>
</details>

<details>
<summary>What are the pros to hipify-perl?</summary>
<br>
  <ul>
    <li>It does not check original code for correctness.</li>
    <li>It does not depend on any other installations.</li>
    <li>It is faster and easier than hipify-clang.</li>
  </ul>
</details>

<details>
<summary>What are the cons of hipify-perl?</summary>
<br>
  <ul>
    <li>There are multiple constructs that it cannot correctly transform (including macros expansion, namespaces, and device/host funciton calls distinguishing).</li>
    <li>It is harder to troubleshoot.</li>
  </ul>
</details>

<details>
<summary>What are the pros to hipify-clang?</summary>
<br>
  <ul>
    <li>It is a true translator, and therefore can handle larger inputs.</li>
    <li>It supports clang options such as `-I` and `-D`.</li>
    <li>It features seamless support of new CUDA versions (as it depends on clang).</li>
  </ul>
</details>

<details>
<summary>What are the cons of hipify-clang?</summary>
<br>
  <ul>
    <li>Incorrect input CUDA code won't be translated to HIP.</li>
    <li>It has more dependencies. For example, CUDA must be installed (as the tool depends on this installation).</li>
  </ul>
</details>
