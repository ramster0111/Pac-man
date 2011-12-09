#include "maps.h"
//#include "config.h"

//#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <list>
#include "config.h"
#include <conio.h>

//#include <cstdlib>
int maps::z=0;
void maps::IncLevel(){
     ++level;
}
maps::maps(){   
                pink=new Ghost(1);
                red=new Ghost(2);
                orange=new Ghost(3);
                brown=new Ghost(4);
                totdots=0;
                ctr=3;
                D=6;
                endFlag=0;
                level=1;
                screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE /*|SDL_FULLSCREEN*/);
                level=1;
                GFX = new graphics(screen);
                GFX -> loadImageData();
                SFX = new audio();
                GFX -> loadFontData();
                SFX -> loadWavSoundData();
                GFX->renderGraphics(26,Player1.GetX(),Player1.GetY());
}
int maps::ghost(){
     if(z%2==0)
     MoveGhost(*red);
     if(z%3==0)
     MoveGhost(*pink);
     if(z%4==0)
     MoveGhost(*orange);
     if(z%5==0)
     MoveGhost(*brown);
     z++;
     return endFlag;
}  
void maps::ReadName(){
   char c;
   std::stringstream name;
   GFX->Flip();
   while(c!=13){
   std::cout<<"entering name";             
   c=getch();
   std::cout<<"\t"<<c<<"\n";
   name<<c;
   }
   GFX->renderGraphics(17,0,0);         
   std::string n = name.str();
   GFX->renderText(1, n.c_str(), 0,150,255, 5, 100);   
     
}
void maps::ChkKill(){
     int ctr=0;
    
  if(red->GetX()==Player1.GetX()&&red->GetY()==Player1.GetY()&&!red->IsPillActive())
       ctr=1; 
  if(orange->GetX()==Player1.GetX()&&orange->GetY()==Player1.GetY()&&!orange->IsPillActive())
       ctr=1;
  if(brown->GetX()==Player1.GetX()&&brown->GetY()==Player1.GetY()&&!brown->IsPillActive())
       ctr=1;
  if(pink->GetX()==Player1.GetX()&&pink->GetY()==Player1.GetY()&&!pink->IsPillActive())
       ctr=1;
  if(ctr==1){
       Player1.Reset();
       red->Reset();
       pink->Reset();
       orange->Reset();
       brown->Reset();
       std::cout<<Player1.getLives();
       if(Player1.getLives()==0){
       std::cout<<"game over";                          
       SFX->playSound(3);
       SDL_Delay(2000);
       GFX->renderGraphics(17,0,0);
       std::cout<<"enter name";
       //ReadName();
       high.input();
       high.handleHighscore(high);
       DisplayHigh();
       endFlag=1;
      }
     if(endFlag==0){
      SFX->playSound(3);
      SDL_Delay(2000);
      GFX->renderGraphics(17,0,0);      
      DrawMap();
      }
   }
   if(red->IsPillActive()&&red->GetX()==Player1.GetX()&&red->GetY()==Player1.GetY())
    {
     red->InitiateKill();
     std::cout<<"Ghost DEad";
    // Player1.BonusScore();
    } 
    if(pink->IsPillActive()&&pink->GetX()==Player1.GetX()&&pink->GetY()==Player1.GetY())
    {
     pink->InitiateKill();
     std::cout<<"Ghost DEad";
    // Player1.BonusScore();
    } 
    if(orange->IsPillActive()&&orange->GetX()==Player1.GetX()&&orange->GetY()==Player1.GetY())
    {
     orange->InitiateKill();
     std::cout<<"Ghost DEad";
    // Player1.BonusScore();
    } 
    if(brown->IsPillActive()&&brown->GetX()==Player1.GetX()&&brown->GetY()==Player1.GetY())
    {
     brown->InitiateKill();
     std::cout<<"Ghost DEad";
     //Player1.BonusScore();
    } 
       
}              
void maps::MoveGhost(Ghost &ghost){
     
    ghost.PacPos(Player1.GetX()/30,Player1.GetY()/30);     
    ghost.SetTarget();     
    switch(ghost.Move()){
                   case 1:
                          //std::cout<<"going up \n";
                          for(int i=0;i<(30/ctr);i++){
                          GFX->renderGraphics(21,ghost.GetX(),ghost.GetY());                                                                                                                      GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());
                          ghost.SetY(ghost.GetY()-ctr);
                          GFX->renderGraphics(21+ghost.RetColor(),ghost.GetX(),ghost.GetY());
                          SDL_Delay(D);
                //std::cout<<MAP[(Player1.GetY())/30-1][(Player1.GetX()/30) ]<<" "<<Player1.GetX()/30<<" "<<Player1.GetY()/30<<std::endl;
                          }
                          if(MAP[(ghost.GetY())/30+1][(ghost.GetX()/30) ]==48)
                          GFX->renderGraphics(16,ghost.GetX(),ghost.GetY()+30);
                          if(MAP[(ghost.GetY())/30+1][(ghost.GetX()/30) ]==57)
                          GFX->renderGraphics(19,ghost.GetX(),ghost.GetY()+30);
                          break;
                   case 2:
                         // std::cout<<"going right \n";
                          for(int i=0;i<(30/ctr);i++){                                                                                                                     GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());
                          GFX->renderGraphics(21,ghost.GetX(),ghost.GetY());
                          ghost.SetX(ghost.GetX()+ctr);
                          GFX->renderGraphics(21+ghost.RetColor(),ghost.GetX(),ghost.GetY());
                          SDL_Delay(D);
                          }
                           if(MAP[(ghost.GetY())/30][(ghost.GetX()/30-1) ]==48)
                          GFX->renderGraphics(16,ghost.GetX()-30,ghost.GetY());
                          break;
                   case 3:
                         // std::cout<<"going down \n";
                          for(int i=0;i<(30/ctr);i++){                                                                                                                     GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());
                          GFX->renderGraphics(21,ghost.GetX(),ghost.GetY());
                          ghost.SetY(ghost.GetY()+ctr);
                          GFX->renderGraphics(21+ghost.RetColor(),ghost.GetX(),ghost.GetY());
                          SDL_Delay(D);
                          }
                          if(MAP[(ghost.GetY())/30-1][(ghost.GetX()/30) ]==48)
                          GFX->renderGraphics(16,ghost.GetX(),ghost.GetY()-30);
                          if(MAP[(ghost.GetY())/30-1][(ghost.GetX()/30) ]==57)
                          GFX->renderGraphics(19,ghost.GetX(),ghost.GetY()-30);
                        break;
                   case 4:
                          //std::cout<<"going left \n";
                          for(int i=0;i<(30/ctr);i++){                                                                                                                     GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());
                          GFX->renderGraphics(21,ghost.GetX(),ghost.GetY());
                          ghost.SetX(ghost.GetX()-ctr);
                          GFX->renderGraphics(21+ghost.RetColor(),ghost.GetX(),ghost.GetY());
                          SDL_Delay(D);
                          }
                           if(MAP[(ghost.GetY())/30][(ghost.GetX()/30)+1 ]==48)
                          GFX->renderGraphics(16,ghost.GetX()+30,ghost.GetY());
                          break;                     
    }
    GFX->renderGraphics(26+Player1.RetFrame(),Player1.GetX(),Player1.GetY());
    GFX->  Flip();
  
}               
             
void maps::MapData(){
     if(level==1){
                FILE *f = fopen("data\\r.txt","r");
                char c;
                
                if (f==NULL) std::cout<<"Error opening file";
                else{
                     MAP.clear();
                    std::cout<<"level 1\n";
                    GFX->renderGraphics(37,230,200);
                    GFX->Flip();
                    SDL_Delay(2000);
                    red->Reset();
                    orange->Reset();
                    pink->Reset();
                    brown->Reset();
                    GFX->renderGraphics(17);
                        for ( int i = 0; i < 18; i++ ){
                            MAP.push_back ( vector<int>() );
                            for ( int j = 0; j < 26; j++ ){
                                c = fgetc (f);
                                if(c == EOF){
                                       fclose (f);
                                       break;
                                }
                                MAP[i].push_back ( (int)c );
                                if(c=='0')
                                totdots++;
                               
                            }
                        }

                        for ( int i = 0; i < 18; i++ ) {
                            for ( int j = 0; j < 26; j++ )
                               cout<<MAP[i][j] <<' ';
                               cout<<'\n';
                        }
                }
      }
      if(level==2){
                FILE *f2 = fopen("data\\r2.txt","r");
                char c2;
                
                if (f2==NULL) std::cout<<"Error opening file";
                else{
                     MAP.clear();
                     GFX->renderGraphics(38,230,200);
                     GFX->Flip();
                     SDL_Delay(2000);
                    red->Reset();
                    orange->Reset();
                    pink->Reset();
                    brown->Reset();
                     GFX->renderGraphics(17);
                    std::cout<<"level 2\n";
                        for ( int i = 0; i < 18; i++ ){
                            MAP.push_back ( vector<int>() );
                            for ( int j = 0; j < 26; j++ ){
                                c2 = fgetc (f2);
                                if(c2 == EOF){
                                       fclose (f2);
                                       break;
                                }
                                MAP[i].push_back ( (int)c2);
                                if(c2=='0')
                                totdots++;
                               
                            }
                        }

                        for ( int i = 0; i < 18; i++ ) {
                            for ( int j = 0; j < 26; j++ )
                               cout<<MAP[i][j] <<' ';
                               cout<<'\n';
                        }
                }
      }
      if(level==3){
                FILE *f3 = fopen("data\\r3.txt","r");
                char c3;
                
                if (f3==NULL) std::cout<<"Error opening file";
                else{
                     
                    MAP.clear();
                    GFX->renderGraphics(39,230,200);
                     GFX->Flip();
                     SDL_Delay(2000);
                    red->Reset();
                    orange->Reset();
                    pink->Reset();
                    brown->Reset();
                    GFX->renderGraphics(17);
                        for ( int i = 0; i < 18; i++ ){
                            MAP.push_back ( vector<int>() );
                            for ( int j = 0; j < 26; j++ ){
                                c3 = fgetc (f3);
                                if(c3 == EOF){
                                       fclose (f3);
                                       break;
                                }
                                MAP[i].push_back ( (int)c3 );
                                if(c3=='0')
                                totdots++;
                               
                            }
                        }

                        for ( int i = 0; i < 18; i++ ) {
                            for ( int j = 0; j < 26; j++ )
                               cout<<MAP[i][j] <<' ';
                               cout<<'\n';
                        }
                }
      }
      if(level==4){
                FILE *f4 = fopen("data\\r4.txt","r");
                char c4;
                
                if (f4==NULL) std::cout<<"Error opening file";
                else{
                     
                    MAP.clear();
                    GFX->renderGraphics(40,230,200);
                     GFX->Flip();
                     SDL_Delay(2000);
                    red->Reset();
                    orange->Reset();
                    pink->Reset();
                    brown->Reset();
                    GFX->renderGraphics(17);
                        for ( int i = 0; i < 18; i++ ){
                            MAP.push_back ( vector<int>() );
                            for ( int j = 0; j < 26; j++ ){
                                c4 = fgetc (f4);
                                if(c4 == EOF){
                                       fclose (f4);
                                       break;
                                }
                                MAP[i].push_back ( (int)c4 );
                                if(c4=='0')
                                totdots++;
                               
                            }
                        }

                        for ( int i = 0; i < 18; i++ ) {
                            for ( int j = 0; j < 26; j++ )
                               cout<<MAP[i][j] <<' ';
                               cout<<'\n';
                        }
                }
      }
      if(level==5){
                FILE *f5 = fopen("data\\r5.txt","r");
                char c5;
                
                if (f5==NULL) std::cout<<"Error opening file";
                else{
                     
                    MAP.clear();
                    GFX->renderGraphics(41,230,200);
                    GFX->Flip();
                    SDL_Delay(2000);
                    GFX->renderGraphics(17);
                        for ( int i = 0; i < 18; i++ ){
                            MAP.push_back ( vector<int>() );
                            for ( int j = 0; j < 26; j++ ){
                                c5 = fgetc (f5);
                                if(c5 == EOF){
                                       fclose (f5);
                                       break;
                                }
                                MAP[i].push_back ( (int)c5 );
                                if(c5=='0')
                                totdots++;
                               
                            }
                        }

                        for ( int i = 0; i < 18; i++ ) {
                            for ( int j = 0; j < 26; j++ )
                               cout<<MAP[i][j] <<' ';
                               cout<<'\n';
                        }
                }
      }         
         
         
         
         
                SFX -> playSound(1); 
                      
}             
int maps::MovePacman(int x){
            
     //DrawMap();
     switch(x){
               
      case 1:if(MAP[Player1.GetY()/30-1][(Player1.GetX())/30]==48|| MAP[Player1.GetY()/30-1][(Player1.GetX())/30]==47||MAP[Player1.GetY()/30-1][(Player1.GetX())/30]==55){
              if(MAP[Player1.GetY()/30-1][(Player1.GetX())/30]==48){
               MAP[Player1.GetY()/30-1][(Player1.GetX())/30]=47;
               SFX -> playSound(2);
               Player1.collectDot();
               if(level*250==Player1.getScore()/10){
               IncLevel();
               Player1.SetX(360);
               Player1.SetY(360);
               GFX->renderGraphics(21,Player1.GetX(),Player1.GetY()); 
               GFX->renderGraphics(17);                                                                                                                    
               MapData();
               DrawMap();
               //return 1;
               }
               itoa (Player1.getScore(),score,10);
               GFX->renderGraphics(30,260,540);
               GFX->renderText(1,score, 50,40,255, 260, 535);              
             }
              if(MAP[Player1.GetY()/30-1][(Player1.GetX())/30]==55){
               MAP[Player1.GetY()/30-1][(Player1.GetX())/30]=47;
               red->ActivatePill();
               orange->ActivatePill();
               brown->ActivatePill();
               pink->ActivatePill();
               Timer=0;
               Timer= SDL_GetTicks();
               std::cout<<Timer;
              }                                                      
              GFX->renderText(2, "Score :", 150,0,255, 5, 540);
              Player1.ChangeFrame(1);
              for(int i=0;i<(30/ctr);i++){
                GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());                                                                                                                     
                Player1.SetY(Player1.GetY()-ctr);
                //DrawMap();
                GFX->renderGraphics(26+Player1.RetFrame(),Player1.GetX(),Player1.GetY());
                
                SDL_Delay(D);
               // std::cout<<MAP[(Player1.GetY())/30-1][(Player1.GetX()/30) ]<<" "<<Player1.GetX()/30<<" "<<Player1.GetY()/30<<std::endl;
              }
             } 
            break;
            
     case 2:if(MAP[(Player1.GetY())/30][Player1.GetX()/30+1]==48|| MAP[(Player1.GetY())/30][Player1.GetX()/30+1]==47||MAP[(Player1.GetY())/30][Player1.GetX()/30+1]==55){
             if(MAP[(Player1.GetY())/30][Player1.GetX()/30+1]==48){
               MAP[(Player1.GetY())/30][Player1.GetX()/30+1]=47;
               SFX -> playSound(2);
               Player1.collectDot();
               if(level*250==Player1.getScore()/10){
               IncLevel();
               Player1.SetX(360);
               Player1.SetY(360);
               GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());                                                                                                                     
               GFX->renderGraphics(17);                                                                                                                    
               MapData();
               DrawMap();
               //return 1;
               }
               itoa (Player1.getScore(),score,10);
               GFX->renderGraphics(30,260,540);
               GFX->renderText(1,score, 50,40,255, 260, 535);  
             }
              if(MAP[(Player1.GetY())/30][Player1.GetX()/30+1]==55){
                MAP[(Player1.GetY())/30][Player1.GetX()/30+1]=47;
                red->ActivatePill();
                orange->ActivatePill();
                brown->ActivatePill();
                pink->ActivatePill();
                Timer=0;
                Timer= SDL_GetTicks();
                std::cout<<Timer;
              } 
             GFX->renderText(2, "Score :", 0,150,255, 5, 540);
             Player1.ChangeFrame(4);
             for(int i=0;i<(30/ctr);i++){
              GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());
              Player1.SetX(Player1.GetX()+ctr);
              GFX->renderGraphics(26+Player1.RetFrame(),Player1.GetX(),Player1.GetY());
              SDL_Delay(D);
             // std::cout<<(MAP[(Player1.GetY())/30][Player1.GetX()/30+1])<<" "<<Player1.GetX()<<" "<<Player1.GetY()<<std::endl;
            }
           }
            break;
            
            
            
     case 3:if(MAP[Player1.GetY()/30+1][(Player1.GetX())/30]==48||MAP[Player1.GetY()/30+1][(Player1.GetX())/30]==47||MAP[Player1.GetY()/30+1][(Player1.GetX())/30]==55){
             if(MAP[Player1.GetY()/30+1][(Player1.GetX())/30]==48){
               MAP[Player1.GetY()/30+1][(Player1.GetX())/30]=47;
               SFX -> playSound(2);
               Player1.collectDot();
               if(level*250==Player1.getScore()/10){
               IncLevel();
               Player1.SetX(360);
               Player1.SetY(360);
               GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());                                                                                                                     
               GFX->renderGraphics(17);                                                                                                                    
               MapData();
               DrawMap();
               //return 1;
               }
               itoa (Player1.getScore(),score,10);
               GFX->renderGraphics(30,260,540);
               GFX->renderText(1,score, 50,40,255, 260, 535);
             }
               if(MAP[Player1.GetY()/30+1][(Player1.GetX())/30]==55){
                  MAP[Player1.GetY()/30+1][(Player1.GetX())/30]=47;
                  red->ActivatePill();
                  orange->ActivatePill();
                  brown->ActivatePill();
                  pink->ActivatePill();
                  Timer=0;
                  Timer= SDL_GetTicks();
                  std::cout<<Timer;
               }
             GFX->renderText(2, "Score :", 150,150,0, 5, 540);
             Player1.ChangeFrame(2);
             for(int i=0;i<(30/ctr);i++){
                     GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());                                                                                                                     
              Player1.SetY(Player1.GetY()+ctr);
              GFX->renderGraphics(26+Player1.RetFrame(),Player1.GetX(),Player1.GetY());
              SDL_Delay(D);
          //    std::cout<<MAP[(Player1.GetY())/30+1][(Player1.GetX()/30) ]<<" "<<Player1.GetX()/30<<" "<<Player1.GetY()/30<<std::endl;
             }
            } 
            break;
            
     case 4:if(MAP[(Player1.GetY())/30][  Player1.GetX()/30-1 ]==48||MAP[(Player1.GetY())/30][  Player1.GetX()/30-1 ]==47||MAP[(Player1.GetY())/30][  Player1.GetX()/30-1 ]==55){
             if(MAP[(Player1.GetY())/30][  Player1.GetX()/30-1 ]==48){
               MAP[(Player1.GetY())/30][  Player1.GetX()/30-1 ]=47;
               SFX -> playSound(2);
               Player1.collectDot();
               if(level*250==Player1.getScore()/10){
               IncLevel();
               Player1.SetX(360);
               Player1.SetY(360);
               GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());                                                                                                                     
               GFX->renderGraphics(17); 
               MapData();                                                                                                                   
               DrawMap();
               //return 1;
               }
               itoa (Player1.getScore(),score,10);
               GFX->renderGraphics(30,260,540);
               GFX->renderText(1,score, 50,40,255, 260, 535);
             }
               if(MAP[(Player1.GetY())/30][  Player1.GetX()/30-1 ]==55){
                 MAP[(Player1.GetY())/30][  Player1.GetX()/30-1 ]=47;
                 red->ActivatePill();
                 orange->ActivatePill();
                 brown->ActivatePill();
                 pink->ActivatePill();
                 Timer=0;
                 Timer= SDL_GetTicks();
                 std::cout<<Timer;
               }
             GFX->renderText(2, "Score :", 0,0,255, 5, 540);
             Player1.ChangeFrame(3);
             for(int i=0;i<(30/ctr);i++){
              GFX->renderGraphics(21,Player1.GetX(),Player1.GetY());
              Player1.SetX(Player1.GetX()-ctr);
              GFX->renderGraphics(26+Player1.RetFrame(),Player1.GetX(),Player1.GetY());
              SDL_Delay(D);
           //   std::cout<<(MAP[(Player1.GetY())/30][Player1.GetX()/30-1])<<" "<<Player1.GetX()<<" "<<Player1.GetY()<<" "<<std::endl;
            }
           } 
            break;
            };  
//red.SetTarget();  
//MoveGhost();
            GFX->renderGraphics(21+red->RetColor(),red->GetX(),red->GetY());
            GFX->renderGraphics(21+pink->RetColor(),pink->GetX(),pink->GetY());
            GFX->renderGraphics(21+orange->RetColor(),orange->GetX(),orange->GetY());
            GFX->renderGraphics(21+brown->RetColor(),brown->GetX(),brown->GetY());
            std::cout<<"totdots\t"<<totdots<<"totdots\t"<<Player1.getScore()/10<<std::endl;
           if ( (SDL_GetTicks()-Timer) > 5000){
                 red->DeActivatePill();
                 orange->DeActivatePill();
                 brown->DeActivatePill();
                 pink->DeActivatePill();
            }
                        
 DisplayLives();              
GFX->  Flip();          
return 0;
}
                       
void maps::DrawMap(){
          for(int x=0;x<18;x++)
             for(int y=0;y<26;y++)  
               switch(MAP[x][y]){
               case 49:
                       GFX->renderGraphics(14,y*30,x*30);
         //        std::cout<<"drawn";
                       break;         
               case 51:
                       GFX->renderGraphics(22,y*30,x*30);//pink
         //        std::cout<<"drawn";
                       break;
               case 52:
                       GFX->renderGraphics(23,y*30,x*30);//red
         //        std::cout<<"drawn";
                       break;
               case 53:
                       GFX->renderGraphics(24,y*30,x*30);//orange
         //        std::cout<<"drawn";
                       break;
               case 54:
                       GFX->renderGraphics(25,y*30,x*30);//brown
         //        std::cout<<"drawn";
                       break;
               case 55:
                       GFX->renderGraphics(15,y*30,x*30);
        //         std::cout<<"drawn";
                       break;  
               case 57:
                       GFX->renderGraphics(19,y*30,x*30);
        //         std::cout<<"drawn";
                       break;  
               case 56:
                       GFX->renderGraphics(26,y*30,x*30);
        //         std::cout<<"drawn";
                       std::cout<<Player1.GetX()<<Player1.GetY()<<totdots; 
                       break; 
               case 50:
                       GFX->renderGraphics(18,y*30,x*30);
        //         std::cout<<"drawn";
                       break; 
               case 48:
                       GFX->renderGraphics(16,y*30,x*30);
         //        std::cout<<"drawn";
                       break;
               case 32:
                       GFX->renderGraphics(21,y*30,x*30);
         //        std::cout<<"drawn";
                       break;          
               };
               GFX->Flip();
         MAP[(Player1.GetY())/30][Player1.GetX()/30]=47;   
         SDL_Delay(3000);    
}
void maps::DisplayLives(){
    int x=0;
    for(int i=0;i<Player1.getLives();i++){
    GFX->renderGraphics(29,710+x,540);
    //GFX->renderGraphics(30,260,540);
    x+=30   ;
    }
}
void maps::DisplayHigh(){
  
  int y=0;
  GFX->renderGraphics(17,0,0);
  GFX->renderText(2, "HIGHSCORES", 0,150,255, 160, 5);
  std::list<Highscore> list;
  Highscore::read(list);
  
  std::list<Highscore>::iterator it = list.begin();
  for(int i=1;it!= list.end(); it++,i++){
      Highscore hs = *it;
      std::stringstream name;
      name << i;
      std::cout<<hs.name;
      std::string n = name.str() + ".  " + hs.name;
      std::cout<<n;
      name.clear();
      GFX->renderText(1, n.c_str(), 0,150,255, 5, 100+y);
      std::stringstream sc;
      sc << hs.score;
      GFX->renderText(1, sc.str().c_str(), 0,150,255, 500, 100+y);
      y+=90;
  }      
  GFX->Flip();
  SDL_Delay(6000);

}

