#include "game.h"
#include<iostream>
#include "config.h"
int game::z=0;
int game::PlayGame(){
                      
               //       SDL_Delay(3000);
                                 //       Map.renderGraphics(17,0,0);
                                 //       SDL_Delay(3000);
                                  //      Map.renderGraphics(12,0,0);
                                  //         SDL_Delay(3000);
                                     
                                   //     Map.renderGraphics(11,0,0);
                                   
                 //                        SDL_PumpEvents();
               
//               SDL_Delay(3000);
                                       
              
               if(z%2==0){
                             if(Map.ghost()){
                             
                             return 1;
                             }
                             
               }
               z++;              
               SDL_Delay(10);
               Map.ChkKill();
                         
                             while( SDL_PollEvent( &event )){      
                           // SDL_PollEvent( &event )  
                             SDL_PumpEvents();
                             keys = SDL_GetKeyState(NULL);
         
                             if( event.type == SDL_QUIT ){
                             return 1;
                             }
                             
                          
                          
                             
                            }   
               
               if ( (SDL_GetTicks()-Timer) > T_FRAME_INTERVAL){
          // - 1 - Update our timer !
                       Timer = SDL_GetTicks();

    
      
                       keys = SDL_GetKeyState(NULL);
                       if ( keys[SDLK_UP] || keys[SDLK_KP8] ) {
                       if(Map.MovePacman(1))
                       return 1;     
                       }
                       if ( keys[SDLK_DOWN] || keys[SDLK_KP2] ) {
                       if(Map.MovePacman(3))
                       return 1;     
                       }
                       if ( keys[SDLK_LEFT] || keys[SDLK_KP4] ) {
                       if(Map.MovePacman(4))
                       return 1;    
                       }
                       if ( keys[SDLK_RIGHT] || keys[SDLK_KP6] ) {
                       if(Map.MovePacman(2))
                       return 1;
                       }
                       if ( keys[SDLK_SPACE] ) {
                       
                       }
                       if ( keys[SDLK_ESCAPE] ) {
                       return 1;
                       }
                   
              } 
              return 0;
}


game::game(){
             Map.MapData();
             Map.DrawMap();
}                 




