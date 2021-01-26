# OpenMP with ROCm

## What is OpenMP?
[OpenMP (Open Multi-Processing)](https://www.openmp.org/) is a "collection of compiler directives, library routines, and environment variables ... for parallelism in C, C++ and Fortran programs [[1](#References)]."

## Why use OpenMP rather than HIP?
While HIP can only take advantage of parallelism on GPUs, OpenMP is portable and can be used on more than GPUs such as CPUs.
OpenMP also provides a way to easily add parallelism to an existing project with less effort than HIP.
This does not mean that OpenMP is superior to HIP. HIP provides more control over what the GPU does and an optimized HIP kernel should out perform OpenMP.

## Installation
If you already installed ROCm > 4.0 you should also already have OpenMP ROCm support. If not, [install ROCm](../IntroToRocm/Intro.md#Installation).

If you are using ROCm < 4.0 install `openmp-extras`.

[Click here for more information on OpenMP support](https://rocmdocs.amd.com/en/latest/Programming_Guides/openmp_support.html).

## How to use OpenMP?
OpenMP can be used using compiler directives such as `#pragma omp parallel`.
Here is some [OpenMP Tutorials](https://www.openmp.org/resources/tutorials-articles/) and [OpenMP Reference Guides](https://www.openmp.org/resources/refguides/).

## Example / Questions
 - [Matrix Multiplication Walkthrough](Examples/MatMul/README.md)
 - [Review questions](Questions.md)

## References

[1] [OpenMP 5.1 Specification](https://www.openmp.org/spec-html/5.1/openmpch1.html)