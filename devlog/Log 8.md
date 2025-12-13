---
Created: 2025-12-13
---

# VTK Structure Revision
After reading further into VTK documentations, forums, and researching using [ChatGPT](https://chatgpt.com). I have come to the conclusion that my current structure, specifically in regards to rendering an animation, will be likely be notably inefficient. 

The loading of a single huge binary file, reading frames with sizes in the tens-of-megabytes, is likely to be destructively slow. Not to mention higher particle of billions. As such, I am electing to create an interpreter to convert my custom binary format to a ```.pvd```, ```.pvtp```, and ```.vtp``` structure. 

The structure uses ```.pvd``` as a timestamp based frame directory to ```.pvtp``` frame files. These ```.pvtp``` files however in-and-of-themselves act as a sort of directory to ```.vtp``` files which each store a piece of the frame.

A ```vtkXMLCollectionReader``` instance will be updated once to create a directory to be used to discern which frames are needed at each time-step. A ```vtkXMLPPolyDataReader``` (note the second "P") will be updated each frame to read the needed ```.pvtp``` file.

The VTK animation system will be used to create the visualisation. 

> [!note] A sub-class of ```vtkCommand``` can be used with animation cues.

