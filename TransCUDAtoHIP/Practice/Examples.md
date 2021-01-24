## Examples

Try downloading some of [the CUDA samples that Nvidia provides on their GitHub](https://github.com/NVIDIA/cuda-samples) to test out both `hipify-perl` and `hipify-clang`.

Testing `hipify-perl`, will still need to compile the result using `hipcc`, and if this fails, you may need to correct for some of the errors of the script.

Testing `hipify-clang` will likely work seamlessly on most of the code in that repo, but feel free to try converting it anyway and ensure it runs correctly on your GPU.