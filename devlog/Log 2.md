---
Created: 2025-11-19
---

# Restructuring
While contemplating the most efficient way to handle the massive amounts of ```Entity``` I realised the massive inefficiency that using a separate object for every particle would cause. I had originally planned to use an arena allocator (allocating a large amount of hopefully contiguous memory to read cold reads). From a CPU standard I do believe this would still have been a viable options, however, I forget this would be massively inefficient in regards to GPU programming (i.e. the whole base of this project).

As such, the following changes will now be made to the structure of the CAMASIM core:
- The ```Particle``` class be removed. Additionally, as this removes any real sensibility in created the base class ```Entity```, which now really on only has one possible derivative, ```Central_Body```.
- The ```Particle_Cloud``` class will now contain multiple arrays to store the various attributes of all particles, using their indexes as identifiers. A notable consideration in regard to the array structure is the storage of particle vectors. This structure will be pivotal to performance.

# ```Particle_Cloud``` Vector Structure
As previously noted, this will be pivotal to absolutely pivotal to the performance of the program. Two current structures come to mind.

## Structure 1
Structure 1 strikes me as the most intuitive, that is creating a separate array for each component of the vector. This would create contiguously accessible memory in regards for computations involving only a single vector component (e.g. comparing x-values of all particles). However, in algorithms necessitating all three vector components this would cause large striding memory access patterns, assuming all memory could be allocated within a contiguous block of memory (though this itself is not assured).

## Structure 2
Structure 2 would involve grouping the three coordinates of each particle's vector sequentially, and those sub-arrays within a single array. This would cause strided memory access patterns (though notably more predictable than the striding pattern mentioned in Structure 1) for algorithms using a single vector component set. In the case of algorithms requiring all three vector components on a per particle basis, this would allow for sequential accessing patterns.

## Decision
As of now, I believe Structure 1 will be the significantly more performant choice. For the following reasons.

As the arrays within ```Particle_Cloud``` will nearly always used in embarrassingly parallel processes via CUDA, having sequentially accessible arrays will be of notable value. While both structures will provide sequential memory accessing in different circumstances, for reasons that will be discussed shortly, I believe Structure 1 will offer this sequential accessing far more frequently.

Additionally, Structure 1 will allow for more fine tuned memory handling between the host and the device as memory can be transferred on a component by component basis while Structure 2 cannot (trivially at least). Furthermore, Structure 1's and Structure 2's performance will be likely be comparable especially with the use of Arena Allocators.

As eluded to before, by the nature of the Cartesian coordinates, that is all components are linearly independent, a large proportion of the algorithms will likely be able to be done on a component by component basis, further supporting Structure 1.2