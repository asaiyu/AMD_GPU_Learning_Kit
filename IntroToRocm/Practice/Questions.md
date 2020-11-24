<details>
<summary>What is ROCm?</summary>
<br>
ROCm is an open-source development platform for GPU computing.
</details>

<details>
<summary>What command can you use to check which version of ROCm you are
using?</summary>
<br>
Running <pre>/opt/rocm/bin/hipconfig --full</pre>will show you which version you are
currently running on your machine.
</details>

<details>
<summary>What programming language should you use to program HIP?</summary>
<br>
HIP is a dialect of C++, and supports templates, classes, lambdas, and other
C++ constructs.
</details>

<details>
<summary>Which compilers does AMD ROCm support?</summary>
<br>
  <ul>
    <li>C++ compiler - Clang++</li>
    <li>C compiler - Clang</li>
    <li>Flang - FORTRAN compiler (FORTRAN 2003 standard)</li>
  </ul>
</details>

<details>
<summary>Why run code on a GPU instead of a CPU?</summary>
<br>
A CPU is designed to handle a lot of tasks quickly. It usually has several
cores, low latency, and can do a handful of operations at once.
A GPU is designed to break complex problems into many smaller tasks and solve
them all at once. It usually has many cores, high throughput, and can do
thousands of operations at once.
</details>
