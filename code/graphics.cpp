

#include "graphics.h"


// GRAPHICS class constructor. Is copies the screen pointer defined 
// in the core class, so as to have direct access to that surface 
// and render images on it
graphics::graphics(SDL_Surface *_screen)
{
    screen = _screen;
    
    for (int i=0; i<IMAGE_COUNT; i++)
        surfaces[i] = NULL;
        
    for (int i=0; i<FONT_COUNT; i++)
        fonts[i] = NULL;
}

// GRAPHICS destructor : for each allocated image, we perform a 
// "clean" release :)
graphics::~graphics()
{
    for (int i=0; i<IMAGE_COUNT; i++)
       if (surfaces[IMAGE_COUNT])
           if( surfaces[i] ) // Is it pointing to anything?
               SDL_FreeSurface( surfaces[i] );

    for (int i=0; i<FONT_COUNT; i++)
       if (fonts[FONT_COUNT])
           if( fonts[i] ) // Cannot destroy fonts that doesn't exist...
               TTF_CloseFont( fonts[i] );

   TTF_Quit(); 
}



// A prototype line drawing function I found on Internet. Very handy,

void graphics::getPixelRGB(int x, int y, Uint8 *r, Uint8 *g, Uint8 *b)
{
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        SDL_GetRGB(*bufp, screen->format, r, g, b);
     
}

// Same "pixel-reading" function except it dosen't read a pixel from 
// the screen but from another SDL_surface
void graphics::getPixelRGB(int x, int y, Uint8 *r, Uint8 *g, Uint8 *b, SDL_Surface* surf)
{
        Uint32 *bufp;
        bufp = (Uint32 *)surf->pixels + y*surf->pitch/4 + x;
        SDL_GetRGB(*bufp, surf->format, r, g, b);
     
}


// This function is what enables transparency in SDL_Surfaces. Without 
// the alpha key colour, SDL graphics would be extremely limited. 
// All you need to do here is specify an image ID and a colour,
// and that colour will become transparent for that specific
// surface      
void graphics::setAlphaColour(int id, Uint32 colour)
{
     if (id <IMAGE_COUNT && id >-1)
     {
        SDL_SetColorKey(surfaces[id],SDL_SRCCOLORKEY|SDL_RLEACCEL,colour);
        surfaces[id] = SDL_DisplayFormatAlpha(surfaces[id]);
     }
}


// Same transparency colour key function as above except it takes
// direct R,G,B values, making it much easier to handle
void graphics::setAlphaColour(int id, int R, int G, int B)
{
     if (id <IMAGE_COUNT && id >-1)
     {
        Uint32 colour = SDL_MapRGB(screen->format, R, G, B);
        setAlphaColour(id, colour);
     }
}


// Image drawing function. This simply writes the SDL surface 
// specified in the ID at the X,Y coordinates
bool graphics::blitImage(int id, int pos_x, int pos_y)
{
     if (id <IMAGE_COUNT && id >-1)
     {
              SDL_Rect dest;
              dest.x = pos_x;
              dest.y = pos_y;
              SDL_BlitSurface(surfaces[id], NULL, screen, &dest);
              return true;
     }
     return false;
}


bool graphics::blitImage(SDL_Surface *surf, int pos_x, int pos_y)
{
     if ( surf )
     {
              SDL_Rect dest;
              dest.x = pos_x;
              dest.y = pos_y;
              SDL_BlitSurface(surf, NULL, screen, &dest);
              return true;
     }
     return false;
}

void graphics::loadImageData()
{
    FILE *f_conf = fopen("data\\images.dat","r");
    if ( !f_conf )
       printf("*** ERROR *** can't load data/images.dat config file\n");
    else 
    {
          printf("Opening image data config file\n");
          printf("==========================================\n");
          char* line = new char[256];
          char* path = new char[256];
          char* data = new char[256];
          
          int nb = 0;
          int alpha;
          
          while (fgets(line,256,f_conf)!=NULL)
          {
              alpha = -1;
              nb = -1;
                
              if ( !strstr( line, "#" ) && (strlen(line)>3) )
              {
                    char* r = line;
                    char* w = data;
                    
                    // Load cell id
                    while (r && *r!='\n' && *r!='\r' && *r!='[')
                          r++;
                    r++;
                    while (r && *r!='\n' && *r!='\r' && *r!=']')
                          *w++ = *r++;
                    *w = 0;
                    nb = atoi(data);
                    w = path;
                    
                    // Load image path id
                    while (r && *r!='\n' && *r!='\r' && *r!='[' )
                          r++;
                    r++;
                    while (r && *r!='\n' && *r!='\r' && *r!=']' )
                          *w++ = *r++;
                    *w = 0;
                    w = data;
                    
                    // Load image alpha boolean
                    while (r && *r!='\n' && *r!='\r' && *r!='[' )
                          r++;
                    r++;
                    while (r && *r!='\n' && *r!='\r' && *r!=']' )
                          *w++ = *r++;
                    *w = 0;
                    alpha = atoi(data);
                    
                    if ( alpha==0 || alpha==1 )
                    {
                         if ( nb > -1 && nb < IMAGE_COUNT)
                         {
                            if ( ! surfaces[nb] )
                            {
                                 if (alpha == 0)
                                 {
                                    printf ("\tLoading image '%s' to cell [%d]\n", path, nb);
                                    SDL_Surface* temp = IMG_Load(path);
                                    surfaces[nb] = SDL_DisplayFormat(temp);
                                    SDL_FreeSurface(temp);
                                 }
                                 else
                                 {
                                    printf ("\tLoading image '%s' to cell [%d] using its alpha channel\n", path, nb);
                                    SDL_Surface* temp = IMG_Load(path);
                                    surfaces[nb] = SDL_DisplayFormatAlpha(temp);
                                    SDL_FreeSurface(temp);
                                 }
                             }
                             else
                                  printf ("\t***ERROR*** cell [%d] has already been allocated... can't load image '%s'\n",nb,path); 
                         }
                         else
                             printf ("\t***ERROR*** Error, can't load image in non allocated memory cell [%d] '%s'!!!!\n",nb, path); 
                         
                    }
                    else
                        printf ("\t***ERROR*** Error, can't load image '%s' : alpha channel value is incorrect !!!!\n",path); 
              }
          }

          delete line;
          delete path;
          delete data;
          fclose(f_conf);
          printf("\n\n");
     }
}


// The function below loads all the fonts defined in the data/fonts.dat
void graphics::loadFontData()
{
    FILE *f_conf = fopen("data/fonts.dat","r");
    if ( !f_conf )
       printf("*** ERROR *** can't load data/fonts.dat config file\n");
    else 
    {
          printf("Opening font data config file\n");
          printf("==========================================\n");
          char* line = new char[256];
          char* path = new char[256];
          char* data = new char[256];
          
          int nb = 0;
          int font_size = 0;
          
          while (fgets(line,256,f_conf)!=NULL)
          {
              nb = -1;
                
              if ( !strstr( line, "#" ) && (strlen(line)>3) )
              {
                    char* r = line;
                    char* w = data;
                    
                    // Load cell id
                    while (r && *r!='\n' && *r!='\r' && *r!='[')
                          r++;
                    r++;
                    while (r && *r!='\n' && *r!='\r' && *r!=']')
                          *w++ = *r++;
                    *w = 0;
                    nb = atoi(data);
                    w = path;
                    
                    // Load font path 
                    while (r && *r!='\n' && *r!='\r' && *r!='[' )
                          r++;
                    r++;
                    while (r && *r!='\n' && *r!='\r' && *r!=']' )
                          *w++ = *r++;
                    *w = 0;
                    w = data;
                    
                    // Load font size 
                    while (r && *r!='\n' && *r!='\r' && *r!='[' )
                          r++;
                    r++;
                    while (r && *r!='\n' && *r!='\r' && *r!=']' )
                          *w++ = *r++;
                    *w = 0;
                    font_size = atoi( data );
                    
                    if ( nb > -1 && nb < FONT_COUNT)
                    {
                            if ( ! fonts[nb] )
                            {
                                 fonts[nb] = TTF_OpenFont( path, font_size );
                                 printf ("\tLoaded font '%s' to cell [%d] using font size '%d'\n", path, nb, font_size); 
                            }
                             else
                                  printf ("\t***ERROR*** cell [%d] has already been allocated... can't load font '%s'\n",nb,path); 
                     }
                     else
                         printf ("\t***ERROR*** Error, can't load font in non allocated memory cell [%d] '%s'!!!!\n",nb, path); 
              }
          }

          delete line;
          delete path;
          delete data;
          fclose(f_conf);
          printf("\n\n");
     }
}

// Font rendering function. The font_id param is used to specify which font you want
// to render on the screen. The next params are the text you want to print out
// and its position on screen...
bool graphics::renderText(int font_id, const char* text, int R, int G, int B, int x, int y)
{
     if ( font_id < FONT_COUNT && font_id > -1 && fonts[font_id] )
     {
          SDL_Color textColor = { R, G, B };
          font_surf = TTF_RenderText_Solid( fonts[font_id], text, textColor );
          blitImage( font_surf, x, y );
          SDL_FreeSurface( font_surf ); // No more memory leaks! \o/ => thanks deps for the bug fix
          font_surf = NULL; 
          return true;
     }
     return false;
}
void graphics::Flip(){    
if( SDL_Flip( screen ) == -1 );
}
void graphics::renderGraphics(int x,int cx,int cy)
{
     blitImage(x,cx,cy);
}
