#ifndef _SDL_HELPER_H_
#define _SDL_HELPER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

static const int SCEEEN_HEIGHT = 1600;
static const int SCREEEN_WIDTH = 900;

struct SDL_Window* createWindow();
struct SDL_Surface* getSurface(struct SDL_Window* window);
struct SDL_Renderer* createRenderer(struct SDL_Window* window);
void setLoadType(int imgLoadType);
struct SDL_Texture* loadTexture(SDL_Renderer* renderer, char* fpath);
void renderImage(SDL_Renderer *renderer, char *image);
void drawRect(SDL_Renderer* renderer, int x, int y);
void reset_screen(SDL_Renderer* renderer);

#endif
