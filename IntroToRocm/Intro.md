# Intro to ROCm

## What is ROCm?

ROCm stands for Radeon Open Compute and is an open-source software development platform for GPU computing.  It is comprised of multiple frameworks including but not limited to Pytorch/Tensorflow, HIP, and more. This platform makes it simpler to write code that utilizes your GPU.


## Why a GPU over a CPU?
A CPU is designed to handle a lot of tasks quickly. It usually has several cores, low latency, and can do a handful of operations at once. A GPU is designed to break complex problems into many smaller tasks and solve them all at once. It usually has many cores, high throughput, and can do thousands of operations at once. Thus a GPU is best used for repetitive operations like that of applying a filter to an image or performing a convolution.


## Installation
Follow the [installation guide](https://rocmdocs.amd.com/en/latest/Installation_Guide/Installation-Guide.html#hip-installation-instructions), and then [verify your installation](https://rocmdocs.amd.com/en/latest/Installation_Guide/Installation-Guide.html#verify-your-installation).

Once installed, you will quickly be able to program in HIP, which is in C++.

Compilers that ROCm supports:

- The C++ compiler that it uses is Clang++.
- The C compiler is Clang.
- The FORTRAN compiler is Flang which is made for the 2003 FORTRAN standard.


## Practice Problems / Questions
A few quick [practice problems](Practice/Questions.md) are available for you to review what was discussed in this short introduction.
