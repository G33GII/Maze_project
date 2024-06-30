#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <stdio.h>

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();


#endif /* HEADER_H */
