#include "maze.h"

/**
 * close:
 * 
 */
void close()
{
    /* Deallocate surface */
    SDL_FreeSurface( helloworld );
    gHelloWorld = NULL;

    /* Destroy window */
    SDL_DestroyWindow( Window );
    gWindow = NULL;

    /* Quit SDL subsystems */
    SDL_Quit();
}