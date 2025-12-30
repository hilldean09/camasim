---
Created: 2025-12-?
---

# CUDA Structure
CUDA related functionality will be compiler into static libraries such that the non-CUDA functionality of the project can be compiled with the most modern C++ features.

CUDA related source code will be kept in the ```cuda``` sub-directory of ```core``` and within the ```CSIM::CSIM_CUDA``` namespace. CUDA kernels, symbols, and other device code will be kept within the ```CSIM::CSIM_CUDA::Kernel``` namespace, and marked with the naming-prefix "```ker_```".

For particle calculations, a one-dimensional thread structure will be used, that is, only the thread-X, block-X, and grid-X dimensions will be used. 

To ensure the kernels can handle the large number of particles, grid-stride patterns will be used frequently, this also has the benefit of thread coarsening (increasing work per thread) which will hopefully assist in preventing the kernel from being memory bond. Note that the memory access per thread will be not be coalesced, however the memory access across each SM and the GPU as a whole will be, hence benchmarking and testing will be beneficial in regards to the pattern used.