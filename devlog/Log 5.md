---
Created: 2025-11-26
---
	
# Processing Structure
To process the simulation, that is, record the simulation state, visualise the recording, and create a video file of said visualisation, a few further layers of abstraction is required. To achieve the aforementioned goals, the following classes will also be implemented:
- The ```Recorder``` class to write the simulation states to a file, and
- The ```Visualiser``` class to create a graphical representation of the data as well as produce a video file of the simulation.

Additionally, ```Visualiser``` will be capable of frame-by-frame walk-through's for more detailed analysis which will be massively beneficial for debugging.

# ```Recorder``` File Output
The ```Recorder``` class will output in binary to a given file name. The output will contain the data necessary to visualise the simulation only. The output will go as follows:
```
[Particle Number], [Frames Total], [Step], [Radii], [Frame 0], [Frame 1], ..., [Frame n]
```

Frame data will be represented as,
```
[Central Body Data], [Particle 1 Data], [Particle 2 Data], ..., [Particle n Data]
```

Central body and particle data will be represented as,
```
[X-Position], [Y-Position], [Z-Position]
```

An alternate frame data representation is,
```
[X-Positions], [Y-Positions], [Z-Positions]
```
Which will be revisited upon further exploration in the graphics library to be used.