//The headers
#include "SDL/SDL.h"
#include "header.h"
#include "SDL/SDL_image.h"

int main( int argc, char* args[] )
{

    //The surfaces
    background= NULL;
    screen = NULL;

    //Quit flag
    bool quit = false;
    
    //Initialize
    if( init() == false )
    {
        return 1;    
    }
    
    //Create a window
    Window myWindow;
    windowFunction (&myWindow);
    
    //If the window failed
    if( error(&myWindow) == true )
    {
        printf("error1 is true\n");
        return 1;    
    }
    
    //Load the files
    if( load_files() == false )
    {
        printf("load files is false\n");
        return 1;    
    }
   
    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {

            //Handle window events
            handle_events(&myWindow);
            
            //If escape was pressed
            if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ) )
            {
                //Quit the program
                quit = true;
            }

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        
        //If the window failed
        if( error(&myWindow) == true )
        {
            printf("error2 is true\n");
            return 1;    
        }
        
        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
        //Show the image centered on the screen
        apply_surface( ( screen->w - background->w ) / 2, ( screen->h - background->h ) / 2, background, screen );
        
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }
    }
    return 0;
}