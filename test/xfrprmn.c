
#include "nrc_types.h"

/* Driver for routine nrc_frprmn */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDIM 3
#define FTOL 1.0e-6
#define PIO2 1.5707963267948966192313216916397514420986

sReal func ( sReal x[] )
{
   return 1.0 - nrc_bessj0 ( x[1]- 0.5 )*nrc_bessj0 ( x[2]- 0.5 )*nrc_bessj0 ( x[3]- 0.5 ); 
}

void dfunc ( sReal x[], sReal df[] )
{
   df[1]= nrc_bessj1 ( x[1]- 0.5 )*nrc_bessj0 ( x[2]- 0.5 )*nrc_bessj0 ( x[3]- 0.5 ); 
   df[2]= nrc_bessj0 ( x[1]- 0.5 )*nrc_bessj1 ( x[2]- 0.5 )*nrc_bessj0 ( x[3]- 0.5 ); 
   df[3]= nrc_bessj0 ( x[1]- 0.5 )*nrc_bessj0 ( x[2]- 0.5 )*nrc_bessj1 ( x[3]- 0.5 ); 
}

int main ( void )
{
   int iter, k; 
   sReal angl, fret, *p; 

   p = nrc_vector ( 1, NDIM ); 
   printf ( "Program finds the minimum of a function\n" ); 
   printf ( "with different trial starting vectors.\n" ); 
   printf ( "True minimum is ( 0.5, 0.5, 0.5 )\n" ); 
   for ( k = 0; k <= 4; k ++ ) {
      angl = PIO2*k/4.0; 
      p[1]= 2.0*cos ( angl ); 
      p[2]= 2.0*sin ( angl ); 
      p[3]= 0.0; 
      printf ( "\nStarting nrc_vector: ( %6.4f, %6.4f, %6.4f )\n", 
         p[1], p[2], p[3] ); 
      nrc_frprmn ( p, NDIM, FTOL, &iter, &fret, func, dfunc ); 
      printf ( "Iterations: %3d\n", iter ); 
      printf ( "Solution nrc_vector: ( %6.4f, %6.4f, %6.4f )\n", 
         p[1], p[2], p[3] ); 
      printf ( "Func. value at solution %14f\n", fret ); 
   }
   nrc_free_vector ( p, 1, NDIM ); 
   return 0; 
}
#undef NRANSI
