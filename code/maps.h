#ifndef  MAPS_H
#define  MAPS_H

#include "core.h"
#include <vector>
#include "player.h"
#include "ghost.h"
#include "high.h"
//class Ghost;
using namespace std;
class maps  {
      
      private: 
               static int z;
               vector<vector<int> > MAP;
               int totdots;
               int level;
               int ctr,D;
               char score [10];
               graphics *GFX;
               SDL_Surface *screen;
               audio *SFX;
               Ghost *red;
               Ghost *pink;
               Ghost *orange;
               Ghost *brown;
               Highscore high;
               int endFlag;
               
               Uint32 Timer;
               
               
       public: 
               Player Player1;
               maps();
            //  ~maps();
               void DrawMap();
               void MapData(); 
               int MovePacman(int);       
               void MoveGhost(Ghost&);
               int ghost();
               void DisplayHigh();
               void ChkKill();
               void DisplayLives();
               void IncLevel();
               void ReadName();
               
      
      
      
      
      
      
      
      };
#endif
