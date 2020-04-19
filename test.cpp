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
   
   SDL_Window* window = window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN );
   if (window == NULL)
   {
      fprintf(stderr,"ERROR in SDL_CreateWindow(): %s\n",SDL_GetError());
      return -1;
   }

   SDL_Renderer* myRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
   if( myRenderer == NULL )
   {
      fprintf(stderr,"Coudln't make renderino %s\n",SDL_GetError());
      return -1;
   }
   
   int imgFlags = IMG_INIT_PNG;
   if( !( IMG_Init( imgFlags ) & imgFlags ) )
   {
   printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
   return -1;
   }


   SDL_Texture* gauge = NULL;
   {
      //Load image at specified path
      SDL_Surface* loadedSurface = IMG_Load( "../gauge.png" );
      if( loadedSurface == NULL )
      {
         printf( "Unable to load image! SDL_image Error: %s\n", IMG_GetError() );
         return -1;
      }
      
      //Create texture from surface pixels
      gauge = SDL_CreateTextureFromSurface( myRenderer, loadedSurface );
      if( gauge == NULL )
      {
         printf( "Unable to create texture SDL Error: %s\n", SDL_GetError() );
      }

      //Get rid of old loaded surface
      SDL_FreeSurface( loadedSurface );
   }
   
   
   SDL_Texture* needle = NULL;
   {
      //Load image at specified path
      SDL_Surface* loadedSurface = IMG_Load( "../needle.png" );
      if( loadedSurface == NULL )
      {
         printf( "Unable to load image! SDL_image Error: %s\n", IMG_GetError() );
         return -1;
      }
      
      //Create texture from surface pixels
      needle = SDL_CreateTextureFromSurface( myRenderer, loadedSurface );
      if( needle == NULL )
      {
         printf( "Unable to create texture SDL Error: %s\n", SDL_GetError() );
      }

      //Get rid of old loaded surface
      SDL_FreeSurface( loadedSurface );
   }
   
   
   bool run = true;
   
   double rotate = 0.0;
   
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
      
      SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear( myRenderer );

      SDL_RenderCopy( myRenderer, gauge, NULL, NULL );
      
      SDL_Rect rectNeedle = {200-10,200,20,200};
      SDL_Point rPoint = {10,0};
      SDL_RenderCopyEx( myRenderer, needle, NULL, &rectNeedle, rotate, &rPoint, SDL_FLIP_VERTICAL);
      rotate += 1.0;
      
      if (rotate >= 360.0)
      {
         rotate = 0.0;
      }
      
      //SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      //SDL_RenderDrawLine(myRenderer, 200, 200, 205, 0);

      SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      
      SDL_RenderPresent(myRenderer);
   }
   
   
   
   SDL_DestroyTexture( gauge );
   SDL_DestroyRenderer(myRenderer);
   SDL_DestroyWindow(window);


   TTF_Quit();
   SDL_Quit();
   return 0;
}
