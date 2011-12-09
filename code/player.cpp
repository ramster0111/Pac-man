#include "Player.h"
#include <iostream>
Player::Player(){
        SetX(360);
        SetY(360);       
        m_iLives = 3;
        m_iScore = 0;
        m_iDots = 0;
        m_bDeath = false;
}
 
int Player::collectDot(){
    
     m_iDots++;
     m_iScore += 10;
    
    // std::cout<<std::endl<<m_iScore<<"  "<<m_iDots<<std::endl;
     return m_iDots;
}
int Player::getDots(){
     return m_iDots;
}
int Player::getLives(){
     return m_iLives;
}
int Player::getScore(){
     return m_iScore;
}
void Player::resetDots(){
      m_iDots = 0;
}
void Player::BonusScore(){
     m_iScore +=100;
}
void Player::Reset(){
     SetX(360);
     SetY(360);
     --m_iLives;
}
void Player::ChangeFrame(int x){
     if(x==1){
     currentFrame=frame_up;
     }
     if(x==2){
     currentFrame=frame_down;
     }
     if(x==3){
     currentFrame=frame_left;
     }
     if(x==4){
     currentFrame=frame_right;
     }   
}
int Player::RetFrame(){
     return currentFrame;     
}
   	 
