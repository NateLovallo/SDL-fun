#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char* args[])
{
	SDL_Surface* screenSurface = NULL;
   
   if (SDL_Init(SDL_INIT_VIDEO) < 0) 
   {
      fprintf(stderr,"ERROR in SDL_Init(): %s\n",SDL_GetError());
      return -1;
   }
   TTF_Init();
   
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
   SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0 ));
   
   // Draw a green box

   //SDL_FillRect(screenSurface,&rectBox,SDL_MapRGB( screenSurface->format, 0, 255, 0 ));
   
   
   
   SDL_Surface* gauge = IMG_Load("../gauge.png");
  
   if (gauge == NULL)
   {
      fprintf(stderr,"Coudln't load image: %s\n",SDL_GetError());
      return -1;
   }
   SDL_Surface* gaugeOptimized = SDL_ConvertSurface( gauge, screenSurface->format, 0 );
   SDL_FreeSurface( gauge );
   
   
   SDL_Surface* needle = IMG_Load("../needle.png");
  
   if (needle == NULL)
   {
      fprintf(stderr,"Coudln't load image: %s\n",SDL_GetError());
      return -1;
   }
   SDL_Surface* needleOptimized = SDL_ConvertSurface( needle, screenSurface->format, 0 );
   SDL_FreeSurface( needle );
   
   
   
   
   
   SDL_Rect rectBg = {0,0,600,400};
   SDL_FillRect(screenSurface,&rectBg,SDL_MapRGB( screenSurface->format, 0, 0, 0 ));
   
   SDL_BlitSurface( gaugeOptimized, NULL, screenSurface, NULL );
   
   SDL_BlitSurface( needleOptimized, NULL, screenSurface, NULL );
   


   bool run = true;
   
   while (run)
   {
      SDL_Event e;
      while( SDL_PollEvent( &e ) != 0 )
      {
         if(e.type == SDL_KEYDOWN)
         {
            run = false;
         }
         else if(e.type == SDL_QUIT)
         {
            run = false;
         }
      }
      
      // Update the surface
      SDL_UpdateWindowSurface( window );
      
   }

   //SDL_DestroyRenderer(renderer);
   //SDL_DestroyWindow(window);


   TTF_Quit();
   SDL_Quit();
   return 0;
}
