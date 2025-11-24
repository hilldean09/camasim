---
Created: 2025-11-24
---
# Position and Velocity Initialisation
The goal distribution for particle positions and velocities within ```Particle_Cloud``` is for the particles to have uniformly distributed directions and normally distributed radii. To achieve this, particle vectors can be generated as polar coordinates, with uniformly distributed polar (XZ-plane) and azimuth (XY) angles, and normally distributed radial components.