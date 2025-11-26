---
Created: 2025-11-26
---

# Processing Structure
To process the simulation, that is, record the simulation state, visualise the recording, and create a video file of said visualisation, a few further layers of abstraction is required. To achieve the aforementioned goals, the following classes will also be implemented:
- The ```Recorder``` class to write the simulation states to a file, and
- The ```Visualiser``` class to create a graphical representation of the data as well as produce a video file of the simulation.

Additionally, ```Visualiser``` will be capable of frame-by-frame walk-through's for more detailed analysis which will be massively beneficial for debugging.