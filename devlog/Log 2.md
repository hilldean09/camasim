# Restructuring
While contemplating the most efficient way to handle the massive amounts of ```Entity``` I realised the massive inefficiency that using a separate object for every particle would cause. I had originally planned to use an arena allocator (allocating a large amount of hopefully contiguous memory to read cold reads). From a CPU standard I do believe this would still have been a viable options, however, I forget this would be massively inefficient in regards to GGPU programming (i.e. the whole base of this project).

As such, the following changes will now be made to the structure of the CAMASIM core:
- The ```Particle``` class be removed. Additionally, as this removes any real sensibility in created the base class ```Entity```, which now really on only has one possible derivative, ```Central_Body```.
- The ```Particle_Cloud``` class will now contain multiple arrays to store the various attributes of all particles, using their indexes as identifiers. A notable consideration in regard to the array structure is the storage of particle vectors. This structure will be pivotal to performance.

# ```Particle_Cloud``` Vector Structure
As previously noted, this will be pivotal to absolutely pivotal to the performance of the program. Two current structures come to mind.

## Structure 1
Structure 1 strikes me as the most intuitive, that is creating a separate array for each component of the vector. This would create contiguously accessible memory in regards for computations involving only a single vector component (e.g. comparing x-values of all particles). However, in algorithms necessitating all three vector components this would cause large jumps 