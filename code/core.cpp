


#include "core.h"
//#include "maps.h"
#include <iostream>
#include "game.h"


// CORE class constructor: initializes SDL, the video mode, window
// title, and enables key repetition
int core::ctr=0;
core::core()
{
    keyctr=-1;
    image=12;
    // Initialize SDL 
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
    {
        printf ("Couldn't initialize SDL : %s\n", SDL_GetError ());
        exit (1);
    }
    
    atexit (SDL_Quit);

    // Set 800x600 32-bits video mode
    screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE /*|SDL_FULLSCREEN*/);
    if (screen == NULL)
    {
        printf ("Couldn't set video mode : %s\n", SDL_GetError ());
        exit (2);
    }
    
    // Enable the TTF font printing library for SDL
    if( TTF_Init() == -1 )
    {
        printf ("Couldn't start SDL TTF : %s\n", SDL_GetError ());
        exit (3);
    }
    
    // Set the title of our application window handler
    SDL_WM_SetCaption ("PaCmaN By Raminder jeet", NULL);
    
    
    // We activate keyboard repetition. Therefore, when a key stays pressed down
    // it will keep moving the image around the screen
    // To see prcisely what this toggle does, just comment the line and recompile
    // the code...
    SDL_EnableKeyRepeat(25, 20);
 
    // Instanciate our graphics controller and load all the image data
    GFXController = new graphics(screen);
//    GFXController -> loadBitmapImageData();

    GFXController -> loadImageData();
    std::cout<<"loading image data";
 
    // Load all fonts needed by the game
    GFXController -> loadFontData();
    
    // Instanciate the sound controller and load sound FX
    SoundController = new audio();
    SoundController -> loadWavSoundData();
    
    
  
}


core::~core()
{
    delete GFXController;
    delete SoundController;
    SDL_FreeSurface( screen );
    SDL_Quit();
}


// The gameLoop function is the heart of the game engine
int core::gameLoop()
{
     // #1 - Handle asynchronous events in queue 
     //      scan for new keypresses or window framework actions
     //      This is mainly for "single" event keys and not the 
     //      game keypresses
     int x_mouse_offset=0;
     int y_mouse_offset=0;
    // int about=0;
     SDL_Event event1;
     
    
    
    
    
     while( SDL_PollEvent( &event ) )
     {      
            SDL_PumpEvents();
            keys = SDL_GetKeyState(NULL);
           
            if( event.type == SDL_QUIT )
              return 1;
           
            if( event.type == SDL_MOUSEMOTION ){
                   x_mouse_offset = event.motion.x; 
                   y_mouse_offset = event.motion.y;
            }
            if(keyctr%3==1)
            image=32; 
            if(keyctr%3==2)
            image=33; 
            if(keyctr%3==0)
            image=13;           
     }//while pollevent
     
     

    if ( (SDL_GetTicks()-Timer) > T_FRAME_INTERVAL )
     {
            Timer = SDL_GetTicks();
            keys = SDL_GetKeyState(NULL);
            if ( keys[SDLK_UP] || keys[SDLK_KP8] ) {
               --keyctr;
               if(keyctr<0)keyctr=2;
               std::cout<<(int)keyctr<<"\n";
               SDL_Delay(100);
            }
            if ( keys[SDLK_DOWN] || keys[SDLK_KP2] ) {
               ++keyctr;
               std::cout<<(int)keyctr<<"\n";
               SDL_Delay(100);
            }
            
            if ( keys[SDLK_LEFT] || keys[SDLK_KP4] ) { }
            if ( keys[SDLK_RIGHT] || keys[SDLK_KP6] ) {  }
            if ( keys[SDLK_SPACE] ) {  }
            if ( keys[SDLK_RETURN] ) {
                 
               SDL_Delay(100);
               if(keyctr%3==0){
                      std::cout<<"start";
                      GFXController->clearScreen(0xFFFFFF);
                      game *Game=new game();
                      while ( Game->PlayGame() == 0 );
               }
               if(keyctr%3==1){
                      std::cout<<"instruction";
                      GFXController->clearScreen(0xFFFFFF);
                      GFXController ->   renderGraphics(35);
                      GFXController ->Flip();
                         //     about=1;
                      SoundController -> playSound(0);
                      while( SDL_WaitEvent(&event1) ){
                                   if( event1.type == SDL_MOUSEBUTTONDOWN )
                                   break;
                                   if( event1.type == SDL_KEYDOWN ){
                                   SDL_Delay(100); 
                                   break; 
                                   }
                      }
               }
               if(keyctr%3==2){
                      std::cout<<"about";
                      GFXController->clearScreen(0xFFFFFF);
                      GFXController->renderGraphics(17);
                      GFXController->renderGraphics(36,200,150);
                      GFXController->Flip();
                         //     about=1;
                      SoundController -> playSound(0);
                      while( SDL_WaitEvent(&event1) ){
                                   if( event1.type == SDL_MOUSEBUTTONDOWN )
                                   break;
                                   if( event1.type == SDL_KEYDOWN ){
                                   SDL_Delay(100); 
                                   break; 
                                   }
                      }
                     
               }      
               
            }
     }       
               
    GFXController -> renderGraphics(image,0,0);
    Animate();
    AnimateCur();    
    GFXController ->Flip();
    //image=12; 
     
            //    return 2;
     
   return 0;
}
void core::Animate(){
        GFXController -> renderGraphics(34,-800+ctr,330);
        ctr+=1;        
        if(ctr==1600)
        ctr=0;        
}
void core::AnimateCur(){
        if(image==32){
                      GFXController -> renderGraphics(29,300-70,450-15);
                      GFXController -> renderGraphics(28,500+40,450-15);
                       
        }
        if(image==33){
                      GFXController -> renderGraphics(29,300+10,500-15);
                      GFXController -> renderGraphics(28,500-40,500-15);     
        }
        if(image==13){
                      GFXController -> renderGraphics(29,300-15,400-15);
                      GFXController -> renderGraphics(28,500-15,400-15);
        }
}

