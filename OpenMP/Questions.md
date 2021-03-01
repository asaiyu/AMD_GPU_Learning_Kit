<details>
<summary>What is OpenMP?</summary>
<br>
OpenMP is an abstraction on multiprocessing for C, C++ and Fortran.
</details>

---

<details>
<summary>Which devices can OpenMP parallelize on?</summary>
<br>

Unlike HIP, OpenMP can parallelize on CPUs, GPUs, FPGAs, etc.

</details>

---

<details>
<summary>How do you make code run on the GPU?</summary>
<br>

Use the `#pragma omp target` construct.

</details>

---

<details>
<summary>How do you parallelize a for-loop?</summary>
<br>

Use the `#pragma omp parallel for` construct.

</details>

---

<details>
<summary>How can you quickly check if your GPU is being utilized?</summary>
<br>

Run `rocm-smi` and check the GPU utilization.

</details>
