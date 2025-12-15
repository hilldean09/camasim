---
Created: 2025-12-15
---

# Radii Binary
While I realised the necessity of writing particles to the VTK compatible format in a deterministic manner, I did not however ensure the reading method would also be deterministic. The needed hoops to ensure this would effectively render everything done so far rather useless. As such, despite the approximately 25% increase in disk space usage, I have decided to attach the radii when writing the particle information.

