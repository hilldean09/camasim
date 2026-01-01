---
Created: 2026-01-01
---

# Octree Generation
For octree generation consider the following optimisations:
```cpp
  if( particle.x > octant.centre.x ) octantIdx |= 4; 
  ...
  ```
I.e. using the bitwise OR assignment operator to utilise the base-8 octant system. Or, 
```cpp
octantIdx |= ( particle.x > octant.centre.x ) ? 4 : 0;
...
```
To reduce thread branching.

To optimisation histogram construction using OpenMP (i.e. "matrix reduction") see [this thread](https://stackoverflow.com/questions/20413995/reducing-on-array-in-openmp) for,
```cpp
#pragma omp parallel
{
    int S_private[10] = {0};
    #pragma omp for
    for (int n=0 ; n<10 ; ++n ) {
        for (int m=0; m<=n; ++m){
            S_private[n] += A[m];
        }
    }
    #pragma omp critical
    {
        for(int n=0; n<10; ++n) {
            S[n] += S_private[n];
        }
    }
}
```
>[!note] ```#pragma omp critical```
>The ```critical``` OpenMP directive is a synchronisation control directive that ensures that only one thread at a time performs the given section of code. In the above case, this prevents race conditions while ensuring all threads update the global array.