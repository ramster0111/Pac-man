//---------------------------------------------------------------//

#ifndef CORE_H
#define CORE_H

#include "config.h"
#include "graphics.h"
#include "audio.h"
//#include "game.h"
//#include "game.h"
//#include "maps.h"
// The CORE class is the center part of our game. It contains
// the game loop, a pointer to the GRAPHICS handler class, the
// performance timer (to control FPS), and the event handling
// is done within the gameLoop function of this class...


class core
{
      public:
              core();
             ~core();
             
             int gameLoop();
             void Animate();
             void AnimateCur();
             void renderGraphics(int x,int cx=0,int cy=0);
             
             SDL_Surface *screen;
              
             graphics *GFXController;
             audio *SoundController;
             
     private:
              
              SDL_Event event;
              Uint32 Timer;
              int image;
              static int ctr;
              int keyctr;
              Uint8* keys;
              
          
              

};
#endif
