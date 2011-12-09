#ifndef GAME_H
#define GAME_H

#include "maps.h"


class game{
      
       private:
               static int z;
               maps Map;
               Uint32 Timer;
               SDL_Event event;
               Uint8* keys;
              
       public:
              game();
              int PlayGame();       
              
      
      
      
      
      
      };
#endif
