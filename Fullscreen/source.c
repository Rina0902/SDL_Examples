//The headers
#include "SDL/SDL.h"
#include "header.h"
#include "SDL/SDL_image.h"

SDL_Surface *load_image( char* filename ) 
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Get the offsets
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}


bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }

    //If eveything loads fine
    return true;    
}

bool load_files()
{
    //Load the background image
    background = load_image( "sky.jpg" );

    
    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;    
    }
    
    //If everything loaded fine
    return true;    
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );

    //Quit SDL
    SDL_Quit();
}

void windowFunction (Window* theWindow)
{
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );
    
    //If there's an error
    if( screen == NULL )
    {
        theWindow->windowOK = false;
        return;
    }
    else
    {
        theWindow->windowOK = true;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Window Event Test", NULL );
    
    //Set window flag
    theWindow->windowed = true;
}

void toggle_fullscreen(Window* theWindow)
{
    //If the screen is windowed
    if( theWindow->windowed == true )
    {
        //Set the screen to fullscreen
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );
                         
        //If there's an error
        if( screen == NULL )
        {
            theWindow->windowOK = false;
            return;
        }
        
        //Set the window state flag
        theWindow->windowed = false;
    }
    //If the screen is fullscreen
    else if( theWindow->windowed == false )
    {
        //Window the screen
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );
                     
        //If there's an error
        if( screen == NULL )
        {
            theWindow->windowOK = false;
            return;
        }
       
        //Set the window state flag
        theWindow->windowed = true;
    }
}

void handle_events(Window* theWindow)
{

    //If there's something wrong with the window
    if( theWindow->windowOK == false )
    {
        printf("theWindow->windowOK == false\n");
        return;    
    }
    
    //If the window resized
    if( event.type == SDL_VIDEORESIZE )
    {
   
        //Resize the screen
        screen = SDL_SetVideoMode( event.resize.w, event.resize.h, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );
        
        //If there's an error
        if( screen == NULL )
        {
            theWindow->windowOK = false;
            return;
        }
    }
      //If enter was pressed
    else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
    {
        //Turn fullscreen on/off
        toggle_fullscreen(theWindow);
        printf("made the function toggle_fullscreen\n ");
    }
     //If the window focus changed
    else if( event.type == SDL_ACTIVEEVENT )
    {
        //If the window was iconified or restored
        if( event.active.state & SDL_APPACTIVE )
        {
            //If the application is no longer active
            if( event.active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Iconified", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Fullscreen", NULL );
            }
        }
           //If something happened to the keyboard focus
        else if( event.active.state & SDL_APPINPUTFOCUS )
        {
            //If the application lost keyboard focus
            if( event.active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Keyboard focus lost", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        //If something happened to the mouse focus
        else if( event.active.state & SDL_APPMOUSEFOCUS )
        {
            //If the application lost mouse focus
            if( event.active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Mouse Focus Lost", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
    }
        //If the window's screen has been altered
    else if( event.type == SDL_VIDEOEXPOSE )
    {
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            //If there's an error
            theWindow->windowOK = false;
            return;
        }
    }
}

bool error(Window* theWindow)
{
    return !theWindow->windowOK;
}