blitzAPI
========

C++/SDL implementation of the BlitzBasic2D API.


Remember BlitzBasic? It has a very easy API, but is stuck at DX7 and the 2D-Part has been discontinued.
This project aims to provide the easy-to-use API for you to use with a proper language ( ;) )...

***How to build***

blitzAPI provides a makefile that should work out of the box and a VisualStudio-Project where the paths will need to be adjusted.

Just provide SDL2, SDL2_Image, SDL2_TTF and a gcc capable of compiling C++11 and you are ready to go!

***How to use***

blitzAPI provides a static library you can link against and a main header (BlitzAPI.h) which is well commented
so figuring out what everything does should be easy.

Where not otherwise stated every function works exactly like it's BB counterpart so you can also consult a manual for BlitzBasic.

***Sample***

See Blitz2D for a very simple example. It won't work because I did not provide the images, but you should be able to replace them^^
