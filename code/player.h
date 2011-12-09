#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player : public Entity
{
private:
     enum Frame {
        frame_up,
        frame_down,
        frame_left,
        frame_right
     };
     Frame currentFrame;
     int m_iDots;
     int m_iLives;
     int m_iScore;
     bool m_bDeath;
     public:
            
     Player();      
     int collectDot();
     int getDots();
   	 int getLives();
   	 int getScore();
   	 void resetDots();
   	 void ChangeFrame(int);
   	 int RetFrame();
   	 void Reset();
   	 void BonusScore();
   	 
   	 
};

#endif
