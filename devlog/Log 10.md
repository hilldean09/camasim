
# CUDA Structure
CUDA related functionality will be compiler into static libraries such that the non-CUDA functionality of the project can be compiled with the most modern C++ features.

CUDA related source code will be kept in the ```cuda``` sub-directory of ```core``` and within the ```CSIM::CSIM_CUDA``` namespace. CUDA kernels, symbols, and other device code will be kept within the ```CSIM::CSIM_CUDA::Kernel``` namespace, and marked with the naming-prefix "```ker_```".

For particle calculations, a one-dimensional thread structure will be used, that is, only the thread-X, block-X, and grid-X