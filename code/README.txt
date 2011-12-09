//////////////////////////////////////////////////
//						//
//	GDO Advanced SDL Engine			//
//						//
//	Game by Marko 	release : 25 July 2006	//
//						//
//	http://www.gamedesign-online.com	//
//						//
//////////////////////////////////////////////////


NOTE :
-------

This engine has been developed under the DevC++ environment,
using the SDL Simple Directmedia Layer library for graphics
rendering and keyboard & mouse input / output. It uses 
additional libraries to render fonts on screen, load wav 
audio files and handle all image formats (jpeg, gif, png... etc)

The loading of bitmap images is still handled seperately in 
order to let the game developer use bitmap transparency key colours
if he had kept that old habbit.

For other image formats, the images.dat file lets you specify whether
you want the engine to attempt to load the alpha channel of your
image or not. The sample code with this engine therefore loads 
the data/img/tux.png in both ways, handling transparency in one case 
only. 

In order to get the engine running, you will need SDL, SDL_Image, SDL_Mixer
and SDL_TTF libraries installed correctly.

Engine Features :
-----------------

- This engine has been put together to run on the DevC++ environment. 
Of course, it can be compiled directly under linux for all the makefile
addicted guys, or use any other windows compiler if needed (VC++, Borland...)

- The engine supports almost all image formats (png, jpeg, bmp, gif... etc...)

- Sounds are handled as WAV files at the moment. An enhancement should soon
enable mp3 sound playing

- All keyboard and mouse input / outputs are handled with this framework


