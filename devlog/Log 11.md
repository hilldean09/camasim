---
Created: 2025-12-29
---
# CUDA Implementation
>[!note] Odd performance results. Using device memory seems to be slower than using host memory. Found as  results of accidentally using host variable for the ```ker_p_aplyVelocity``` function.

Likely cause is the massive amounts of ```cudaMalloc``` and ```cudaFree``` used. Will reconfigure to "allocate once and reuse."