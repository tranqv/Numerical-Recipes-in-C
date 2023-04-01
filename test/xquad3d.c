
#include "nrc_types.h"

/* Driver for routine nrc_quad3d */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define PI 3.141592653589793238462643383279502884197
#define NVAL 10

static sReal xmax; 

sReal func ( sReal x, sReal y, sReal z )
{
   return x*x + y*y + z*z; 
}

sReal z1 ( sReal x, sReal y )
{
   return ( sReal ) - sqrt ( xmax*xmax - x*x - y*y ); 
}

sReal z2 ( sReal x, sReal y )
{
   return ( sReal ) sqrt ( xmax*xmax - x*x - y*y ); 
}

sReal yy1 ( sReal x )
{
   return ( sReal ) - sqrt ( xmax*xmax - x*x ); 
}

sReal yy2 ( sReal x )
{
   return ( sReal ) sqrt ( xmax*xmax - x*x ); 
}

int main ( void )
{
   int i; 
   sReal xmin, s; 

   printf ( "Integral of r^2 over a spherical volume\n\n" ); 
   printf ( "%13s %10s %11s\n", "radius", "QUAD3D", "Actual" ); 
   for ( i = 1; i <= NVAL; i ++ ) {
      xmax = 0.1*i; 
      xmin = - xmax; 
      s = nrc_quad3d ( func, xmin, xmax ); 
      printf ( "%12.2f %12.6f %11.6f\n", 
         xmax, s, 4.0*PI*pow ( xmax, 5.0 )/5.0 ); 
   }
   return 0; 
}
#undef NRANSI
