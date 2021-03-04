#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdbool.h>


//The surfaces
SDL_Surface *background;
SDL_Surface *screen;

typedef struct Window
{
    //Whether the window is windowed or not
    bool windowed;
    
    //Whether the window is fine
    bool windowOK;
    
} Window ;

//Screen attributes
int SCREEN_WIDTH ;
int SCREEN_HEIGHT;
int SCREEN_BPP ;


//The event structure that will be used
SDL_Event event;

//Functions:
SDL_Surface *load_image( char* filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
bool init();
bool load_files();
void clean_up();
void windowFunction (Window* thewindow);
//Handle window events
void handle_events(Window* theWindow);

//Turn fullscreen on/off
void toggle_fullscreen(Window* theWindow);

//Check if anything's wrong with the window
bool error(Window* theWindow);


#endif