#include <raylib.h>
// #include "vis-fractal.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 300
#define HEIGHT 300
#define ITMAX 100


const double rMin   = -2.;
const double rMax   = .5;
const double iMin   = -1;
const double iMax   = 1;

const int red    = 0xfe;
const int green  = 0xef;
const int blue   = 0xfe;


typedef struct { 
       double r, i;
} c_double;

#define make_c_double(r,i) ((c_double){(r),(i)})


double
c_abs_double(c_double z){
       return sqrt(z.r*z.r+z.i*z.i);
}

c_double
c_sqr_double(c_double z){ /* z^2 = (a+bi)^2 = a^2 - b^2 + 2abi*/
       return make_c_double(z.r*z.r - z.i*z.i, 2*z.r*z.i);
}

double
manthelbrothel(c_double a)
{
       size_t it = 0;
       c_double z = make_c_double(0.0,0.0);
       for(z = a; it < ITMAX && c_abs_double(z) < 2; it++){
              z = c_sqr_double(z);
              z.r += a.r;
              z.i += a.i;
              it++;
       }
      
       return (double)(ITMAX-it)/ITMAX;
}

int
main()
{
       double scale = (double)WIDTH/(rMax-rMin);
       //double height = (double)scale*HEIGHT;
       Color color = RED;
       SetConfigFlags(FLAG_WINDOW_RESIZABLE);
       InitWindow(WIDTH, HEIGHT, "display fractal");
       double fesc = 0.0;

       int width = WIDTH;
       int height = WIDTH;

       int key;

       SetTargetFPS(30);
       for(;;){
              BeginDrawing();
             
              if(IsWindowResized()){
                     width = GetScreenWidth();
                     height = GetScreenHeight();
                     scale = (double)width/(rMax-rMin);
              } 
              key = GetKeyPressed();
              if(key > 32  && key < 0xff && key != 127){ // printable ascii char
                     break;
              }
              for(int x = 0; x < width; x++){
                     for(int y = 0; y < height; y++){
                            fesc = manthelbrothel(
                                      make_c_double((double)x/scale+rMin,
                                                    (double)y/scale+iMin
                            ));

                            color.r=red*fesc;
                            color.g=green*fesc;
                            color.b=blue*fesc;
                            color.a=0xff;

                            DrawPixel(x, y, color);
                     }
              }
              
              EndDrawing();
       }
}


