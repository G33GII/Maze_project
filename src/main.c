#include "maze.h"

#define FLOOR_HORIZONTAL 1

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24


int worldMap[mapWidth][mapHeight] =
    {
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 6, 4, 4, 6, 4, 6, 4, 4, 4, 6, 4},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
        {8, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
        {8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 6, 6, 6, 0, 6, 4, 6},
        {8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 6, 0, 0, 0, 0, 0, 6},
        {7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 8, 0, 8, 0, 8, 0, 8, 4, 0, 4, 0, 6, 0, 6},
        {7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 0, 0, 0, 0, 0, 6},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 0, 0, 0, 0, 4},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 6, 0, 6, 0, 6},
        {7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 4, 6, 0, 6, 6, 6},
        {7, 7, 7, 7, 0, 7, 7, 7, 7, 8, 8, 4, 0, 6, 8, 4, 8, 3, 3, 3, 0, 3, 3, 3},
        {2, 2, 2, 2, 0, 2, 2, 2, 2, 4, 6, 4, 0, 0, 6, 0, 6, 3, 0, 0, 0, 0, 0, 3},
        {2, 2, 0, 0, 0, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4, 6, 0, 6, 3, 3, 0, 0, 0, 3, 3},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 2, 2, 2, 6, 6, 0, 0, 5, 0, 5, 0, 5},
        {2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5},
        {2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5},
        {2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5}};

Uint32 buffer[screenHeight][screenWidth]; // y-coordinate first because it works per scanline

unsigned long loadImage(Uint32 *texture, unsigned long *tw, unsigned long *th, const char *filename)
{
    SDL_Surface *image = IMG_Load(filename);
    if (!image)
    {
        printf("Failed to load image %s: %s\n", filename, IMG_GetError());
        return 1;
    }
    if (image->w != texWidth || image->h != texHeight)
    {
        printf("Image %s must be %dx%d\n", filename, texWidth, texHeight);
        SDL_FreeSurface(image);
        return 1;
    }
    memcpy(texture, image->pixels, texWidth * texHeight * sizeof(Uint32));
    SDL_FreeSurface(image);
    *tw = texWidth;
    *th = texHeight;
    return 0;
}

int main(int argc, char *argv[])
{
    double posX = 22.0, posY = 11.5;    // x and y start position
    double dirX = -1.0, dirY = 0.0;     // initial direction vector
    double planeX = 0.0, planeY = 0.66; // the 2d raycaster version of camera plane

    double time = 0;    // time of current frame
    double oldTime = 0; // time of previous frame

    Uint32 *texture[8];
    for (int i = 0; i < 8; i++)
    {
        texture[i] = (Uint32 *)malloc(texWidth * texHeight * sizeof(Uint32));
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);

    unsigned long tw, th, error = 0;
#if 1
  for(int x = 0; x < texWidth; x++)
  for(int y = 0; y < texHeight; y++)
  {
    int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
    //int xcolor = x * 256 / texWidth;
    int ycolor = y * 256 / texHeight;
    int xycolor = y * 128 / texHeight + x * 128 / texWidth;
    texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
    texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
    texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
    texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
    texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
  }
#else
    // load some textures
    error |= loadImage(texture[0], &tw, &th, "pics/eagle.png");
    error |= loadImage(texture[1], &tw, &th, "pics/redbrick.png");
    error |= loadImage(texture[2], &tw, &th, "pics/purplestone.png");
    error |= loadImage(texture[3], &tw, &th, "pics/wood.png");
    error |= loadImage(texture[4], &tw, &th, "pics/bluestone.png");
    error |= loadImage(texture[5], &tw, &th, "pics/mossy.png");
    error |= loadImage(texture[6], &tw, &th, "pics/greystone.png");
    error |= loadImage(texture[7], &tw, &th, "pics/colorstone.png");
    if (error)
    {
        printf("error loading images\n");
        return 1;
    }
#endif

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

#if FLOOR_HORIZONTAL
        for (int y = screenHeight / 2 + 1; y < screenHeight; ++y)
        {
            float rayDirX0 = dirX - planeX;
            float rayDirY0 = dirY - planeY;
            float rayDirX1 = dirX + planeX;
            float rayDirY1 = dirY + planeY;

            int p = y - screenHeight / 2;

            float posZ = 0.5 * screenHeight;

            float rowDistance = posZ / p;

            float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
            float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

            float floorX = posX + rowDistance * rayDirX0;
            float floorY = posY + rowDistance * rayDirY0;

            for (int x = 0; x < screenWidth; ++x)
            {
                int cellX = (int)(floorX);
                int cellY = (int)(floorY);

                int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
                int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

                floorX += floorStepX;
                floorY += floorStepY;

                int floorTexture = 3;
                int ceilingTexture = 6;

                Uint32 color;
                color = texture[floorTexture][texWidth * ty + tx];
                color = (color >> 1) & 8355711;
                buffer[y][x] = color;

                color = texture[ceilingTexture][texWidth * ty + tx];
                color = (color >> 1) & 8355711;
                buffer[screenHeight - y - 1][x] = color;
            }
        }
#endif

        for (int x = 0; x < screenWidth; x++)
        {
            double cameraX = 2 * x / (double)screenWidth - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            int mapX = (int)posX;
            int mapY = (int)posY;

            double sideDistX;
            double sideDistY;

            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
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

            int texNum = worldMap[mapX][mapY] - 1;

            double wallX;
            if (side == 0)
                wallX = posY + perpWallDist * rayDirY;
            else
                wallX = posX + perpWallDist * rayDirX;
            wallX -= floor(wallX);

            int texX = (int)(wallX * (double)texWidth);
            if (side == 0 && rayDirX > 0)
                texX = texWidth - texX - 1;
            if (side == 1 && rayDirY < 0)
                texX = texWidth - texX - 1;

            for (int y = drawStart; y < drawEnd; y++)
            {
                int d = y * 256 - screenHeight * 128 + lineHeight * 128;
                int texY = ((d * texHeight) / lineHeight) / 256;
                Uint32 color = texture[texNum][texHeight * texY + texX];
                if (side == 1)
                    color = (color >> 1) & 8355711;
                buffer[y][x] = color;
            }
        }

        SDL_UpdateTexture(sdlTexture, NULL, buffer, screenWidth * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
        SDL_RenderPresent(renderer);

        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;

        double moveSpeed = frameTime * 5.0;
        double rotSpeed = frameTime * 3.0;

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP])
        {
            if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == false)
                posX += dirX * moveSpeed;
            if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == false)
                posY += dirY * moveSpeed;
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == false)
                posX -= dirX * moveSpeed;
            if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == false)
                posY -= dirY * moveSpeed;
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
        if (state[SDL_SCANCODE_LEFT])
        {
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        free(texture[i]);
    }

    SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
