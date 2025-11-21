---
Created: 2025-11-21
---
# Collision Simulation
To round out the attributes of ```Particle_Cloud```, variables related to collision handling will be required. In researching this, I have found the following [equations for calculating the velocity of two bodies after collision with variable elasticity](https://www.mathsisfun.com/physics/collisions.html):
$$v_{a}=\frac{elast \times m_{b} \left( v_{b} - v_{a} \right) + m_{a}v_{a} + m_{b}v_{b}}{ m_{a} + m_{b} }$$
$$v_{b}=\frac{elast \times m_{a} \left( v_{a} - v_{b} \right) + m_{a}v_{a} + m_{b}v_{b}}{ m_{a} + m_{b} }$$

These equations will be used to simulate collisions between particles.

This approach however causes another issue, to properly simulate multi-body collisions, the effects of previously calculated collisions must be considered for following collisions within a frame. This would effectively prevent massively parallel computation of particle collisions, although collision detection can still be done with massive parallelism which should hopefully compensate.

Additionally, the coefficient of restitution (i.e elasticity of the collision) will be stored as a partial coefficient of restitution for each particle. Note that, to reduce the amount of division performed on the GPU (though fast division by bit shifting is possible in this circumstance), the partial coefficients of restitution will be stored as values from 0 to 0.5 and will summed on a per collision basis as opposed to averaged.

# Handling CUDA Device Output
While considering collision handling I recalled my need for a output structure to store the changes to be applied the original structure at the end of a step in a previous project. Fortunately, this will be noted required in this project (as of currently) for the following reasons:
- collision handling requires constantly up-to-date values within the step,
- gravity calculations are independent of velocity (as positions will not be updated).and
- gravity calculations are independent of collisions.
>[!note] Possible Opportunity for simultaneous collision handling (on CPU) and gravity simulation (on GPU).