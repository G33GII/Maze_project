#include "maze.h"

SDL_Texture *textures[NUM_TEXTURES];

/**
 * main:
 * @argc:
 * @argv:
 */
int main(int argc, char *argv[])
{
    int screenWidth = 800;
    int screenHeight = 600;
    bool quit = false;
    bool showMap = true;
    double moveSpeed = 0.05;
    double rotSpeed = 0.03;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <mapfile>\n", argv[0]);
        return -1;
    }

    loadMap(argv[1]); /* Load the world map data from a file */

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    

    while (!quit)
    {
        handle_input(&quit, &moveSpeed, &rotSpeed, &screenWidth, &screenHeight);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        render(renderer, screenWidth, screenHeight);

        if (showMap)
        {
            drawMap(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
