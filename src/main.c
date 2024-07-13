#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#define NUM_TEXTURES 11

/* The world map */
int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

double posX = 22, posY = 12;      // player position
double dirX = -1, dirY = 0;       // player direction vector
double planeX = 0, planeY = 0.66; // camera plane
SDL_Texture *textures[NUM_TEXTURES];



void render(SDL_Renderer *renderer, int screenWidth, int screenHeight)
{
    // Draw the ceiling
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
    SDL_Rect ceilingRect = {0, 0, screenWidth, screenHeight / 2};
    SDL_RenderFillRect(renderer, &ceilingRect);

    // Draw the floor
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Green
    SDL_Rect floorRect = {0, screenHeight / 2, screenWidth, screenHeight / 2};
    SDL_RenderFillRect(renderer, &floorRect);

    for (int x = 0; x < screenWidth; x++)
    {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if (side == 1)
            SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}

void handle_input(bool *quit, double *moveSpeed, double *rotSpeed, int *screenWidth, int *screenHeight)
{
    SDL_Event event;
    int mouseX, mouseY;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            *quit = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                *quit = true;
            }
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            int xrel = event.motion.xrel;
            double rotAngle = xrel * (*rotSpeed);

            double oldDirX = dirX;
            dirX = dirX * cos(-rotAngle) - dirY * sin(-rotAngle);
            dirY = oldDirX * sin(-rotAngle) + dirY * cos(-rotAngle);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotAngle) - planeY * sin(-rotAngle);
            planeY = oldPlaneX * sin(-rotAngle) + planeY * cos(-rotAngle);
        }
        else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            *screenWidth = event.window.data1;
            *screenHeight = event.window.data2;
        }
    }

    if (keystate[SDL_SCANCODE_UP])
    {
        if (worldMap[(int)(posX + dirX * (*moveSpeed))][(int)(posY)] == 0)
            posX += dirX * (*moveSpeed);
        if (worldMap[(int)(posX)][(int)(posY + dirY * (*moveSpeed))] == 0)
            posY += dirY * (*moveSpeed);
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        if (worldMap[(int)(posX - dirX * (*moveSpeed))][(int)(posY)] == 0)
            posX -= dirX * (*moveSpeed);
        if (worldMap[(int)(posX)][(int)(posY - dirY * (*moveSpeed))] == 0)
            posY -= dirY * (*moveSpeed);
    }
    if (keystate[SDL_SCANCODE_LEFT])
    {
        double oldDirX = dirX;
        dirX = dirX * cos(*rotSpeed) - dirY * sin(*rotSpeed);
        dirY = oldDirX * sin(*rotSpeed) + dirY * cos(*rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(*rotSpeed) - planeY * sin(*rotSpeed);
        planeY = oldPlaneX * sin(*rotSpeed) + planeY * cos(*rotSpeed);
    }
    if (keystate[SDL_SCANCODE_RIGHT])
    {
        double oldDirX = dirX;
        dirX = dirX * cos(-*rotSpeed) - dirY * sin(-*rotSpeed);
        dirY = oldDirX * sin(-*rotSpeed) + dirY * cos(-*rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-*rotSpeed) - planeY * sin(-*rotSpeed);
        planeY = oldPlaneX * sin(-*rotSpeed) + planeY * cos(-*rotSpeed);
    }
}


void drawMap(SDL_Renderer *renderer)
{
    int mapScale = 4;                                     /* Scale down the map to fit on the screen */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); /* White for walls */
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (worldMap[x][y] > 0)
            {
                SDL_Rect rect = {x * mapScale, y * mapScale, mapScale, mapScale};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    /* Draw the player on the map */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /* Red for player */
    SDL_Rect playerRect = {posX * mapScale - mapScale / 2, posY * mapScale - mapScale / 2, mapScale, mapScale};
    SDL_RenderFillRect(renderer, &playerRect);

    /* Draw the direction line */
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); /* Green for direction */
    int lineX = posX * mapScale + dirX * mapScale;
    int lineY = posY * mapScale + dirY * mapScale;
    SDL_RenderDrawLine(renderer, posX * mapScale, posY * mapScale, lineX, lineY);
}

/*Function to load the map from a file*/ 
void loadMap(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open map file: %s\n", filename);
        exit(1);
    }

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (fscanf(file, "%d", &worldMap[x][y]) != 1)
            {
                fprintf(stderr, "Invalid map format\n");
                fclose(file);
                exit(1);
            }
        }
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <mapfile>\n", argv[0]);
        return -1;
    }

    loadMap(argv[1]);

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

    int screenWidth = 800;
    int screenHeight = 600;
    bool quit = false;
    bool showMap = true;
    double moveSpeed = 0.05;
    double rotSpeed = 0.03;

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
