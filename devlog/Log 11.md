---
Created: 2025-12-29
---

# CUDA Implementation
>[!note] Odd performance results. Using device memory seems to be slower than using host memory. Found as  results of accidentally using host variable for the ```ker_p_aplyVelocity``` function.
>Likely cause is the massive amounts of ```cudaMalloc``` and ```cudaFree``` used. Will reconfigure to "allocate once and reuse."

# Octrees
To efficiently implement both collision and gravity simulation, the octree structure will be employed. The octree structure allows for both the collision detection / handling algorithms (via local octant bounding) and gravity algorithms (via the Barnes-Hut process for long ranged forces) to be computed as, $$ O \left( n \times \log{ n } \right) $$ as opposed to direct algorithms of, $$ O \left( n^2 \right) $$ though sacrificing some accuracy. However, given CAMASIM's goal as an approximation and visualisation tool, this is acceptable. Furthermore, as both the collision and gravity can reuse the same octree per frame, this will hide much of the overhead that would be incurred.

To implement the octree, I will use a variation on the typical structure. The octree will work with an array of indexes equal to the number of particles in the simulation, each index representing a particle ID (PID). Each octant will "store" the particles it contains by defining a sub-array within the array with bounding indexes (inclusive-exclusive), particles will be sorted into the octants by moving their corresponding PID's throughout the arrays and sub-arrays. This approach will be more compatible with my current structure, however, it will likely have poor cache locality. Furthermore, this approach can also be readily parallelised using OpenMP.

Octants will continue sub-dividing until the number of particles it contains is less than a given number. 

The octant class structure will need to have member variables for its **bounding indexes within the PID array**, **its parent octant** (except for the root octant which will use its own variation on the structure), **its children**, **it's centre of mass**, and it's **spatial bounds** (defined using two opposite corners).

Note that moving PID's through large octant bounds will be particularly costly at, $$ O \left( n \right) $$  per relocation. A possible optimisation is batching relocations, which does not improve time-complexity will decrease the number of memory swaps needed at the cost of more memory and arithmetic overhead. Hopefully, a sufficient batch size can hide the overhead, especially for lower level (and thus more dense) octants.
>[!failure]
>This turned out to be pretty much flat out silly, using a temporary array for storing desired states is likely to be significantly easier and probably performant. A case of KISS.
