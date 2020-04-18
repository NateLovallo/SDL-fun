#include <SDL2/SDL.h>

// Main entrypoint
int main(int argc, char* args[])
{
	SDL_Surface* screenSurface = NULL;
   
   if (SDL_Init(SDL_INIT_VIDEO) < 0) 
   {
      fprintf(stderr,"ERROR in SDL_Init(): %s\n",SDL_GetError());
      return -1;
   }
   SDL_ShowCursor(SDL_DISABLE);
   
   SDL_Window* window = window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN );
   if (window == NULL)
   {
      fprintf(stderr,"ERROR in SDL_CreateWindow(): %s\n",SDL_GetError());
      return -1;
   }
   
   // Get window surface
   screenSurface = SDL_GetWindowSurface( window );

   // Fill the surface black
   SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0 ) );
   
   // Draw a green box
   SDL_Rect rectBox = {0,0,100,100};
   SDL_FillRect(screenSurface,&rectBox,SDL_MapRGB( screenSurface->format, 0, 255, 0 ) );
   

   // Update the surface
   SDL_UpdateWindowSurface( window );

   bool run = true;
   
   while (run)
   {
      SDL_Event e;
      while( SDL_PollEvent( &e ) != 0 )
      {
         if( e.type == SDL_KEYDOWN )
         {
            run = false;
         }
      }
      
   }

   
   

   return 0;
}
