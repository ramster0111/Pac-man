#ifndef GHOST_H
#define GHOST_H
#include"entity.h"
#include"search.h"

class Ghost : public Entity
{
private:
        int targetNx;
        int targetNy;
        int targetFx;
        int targetFy;
        int Color;
        int pill;
        bool Dead; 
public:
        Ghost();
        Ghost(int color);
        int SetTarget();
        void PacPos(int,int);
        int Move();
        int RetColor();
        void Reset();
        void ActivatePill();
        void DeActivatePill();
        int IsPillActive();
        void InitiateKill();
};




#endif
