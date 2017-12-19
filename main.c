#include "position/position.h"
#include "sdl_helper/sdl_helper.h"

void main()
{
    struct position* pos = init_position(40, 400);
    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;

    window = createWindow();
    renderer = createRenderer(window);

    SDL_Event event;
    int  hasquit = -1;
    
    reset_screen(renderer);
    drawRect(renderer, get_x(pos), get_y(pos));        
    while(hasquit != 0)
    {
        while(hasquit != 0 && SDL_PollEvent(&event)!=0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    hasquit = 0;
                break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                     {
                        case SDL_SCANCODE_LEFT:
                            accelerate(pos, -100, 0);
                        break;
                        case SDL_SCANCODE_RIGHT:
                            accelerate(pos, 100, 0);
                        break;
                        case SDL_SCANCODE_UP:
                            accelerate(pos, 0, -100);
                        break;
                        case SDL_SCANCODE_DOWN:
                            accelerate(pos, 0, 100);
                        break;

                    }
                break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                     {
                        case SDL_SCANCODE_LEFT:
                            accelerate(pos, 100, 0);
                        break;
                        case SDL_SCANCODE_RIGHT:
                            accelerate(pos, -100, 0);
                        break;
                        case SDL_SCANCODE_UP:
                            accelerate(pos, 0, 100);
                        break;
                        case SDL_SCANCODE_DOWN:
                            accelerate(pos, 0, -100);
                        break;

                    }
                break;
            }
            
        }
        reset_screen(renderer);
        drawRect(renderer, get_x(pos), get_y(pos));        
        SDL_Delay(100);
    }
    destroy_position(pos);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}
