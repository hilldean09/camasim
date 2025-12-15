---
Created: 2025-12-13
---

# VTK Structure Revision
After reading further into VTK documentations, forums, and researching using [ChatGPT](https://chatgpt.com). I have come to the conclusion that my current structure, specifically in regards to rendering an animation, will be likely be notably inefficient. 

The loading of a single huge binary file, reading frames with sizes in the tens-of-megabytes, is likely to be destructively slow. Not to mention higher particle counts like billions. As such, I am electing to create an interpreter to convert my custom binary format to a ```.pvd```, ```.pvtp```, and ```.vtp``` structure. 

The structure uses ```.pvd``` as a timestamp based frame directory to ```.pvtp``` frame files. These ```.pvtp``` files however in-and-of-themselves act as a sort of directory to ```.vtp``` files which each store a piece of the frame.

A ```vtkXMLCollectionReader``` instance will be updated once to create a directory to be used to discern which frames are needed at each time-step. A ```vtkXMLPPolyDataReader``` (note the second "P") will be updated each frame to read the needed ```.pvtp``` file.

The VTK animation system will be used to create the visualisation. 

> [!note] A sub-class of ```vtkCommand``` can be used with animation cues.

Additionally, to avoid repeated storage of the radii data the radii will be kept in its own separate binary. This does cause the issue of linking the radii with the VTK poly-data structure, however, this can be maintained by ensuring deterministic storage of the particle within the ```.vtp``` files.

# Custom Binary To VTK
To maintain deterministic particle storage within the ```.vtp``` frame file collections, each piece will be written explicitly using ```vtkXMLPolyDataWriter```. The names of these ```.vtp``` files will be stored then passed to a function to write the ```.pvtp``` files using ```vtkXMLUtilities``` and ```vtkXMLDataElement```. 

The ```.pvd``` files seems to need to be written manually.

# File-system navigation
Note the migration to the use of the ```<filesystem>``` standard library in the ```Interpreter``` class. As well as increased use of ```std::string```. This is a result of my becoming more comfortable with these tools.


