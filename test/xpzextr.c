
#include "nrc_types.h"

/* Driver for routine nrc_pzextr */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NV 4
#define IMAXX 10

sReal **d, *x; /* defining declaration */

int main ( void )
{
   int i, iest, j; 
   sReal dum, xest, *dy, *yest, *yz; 

   dy = nrc_vector ( 1, NV ); 
   yest = nrc_vector ( 1, NV ); 
   yz = nrc_vector ( 1, NV ); 
   x = nrc_vector ( 1, IMAXX ); 
   d = nrc_matrix ( 1, IMAXX, 1, IMAXX ); 
   /* Feed values from a rational function */
   /* fn ( x )=( 1 - x + x**3 )/( x + 1 )**n */
   for ( i = 1; i <= IMAXX; i ++ ) {
      iest = i; 
      xest = 1.0/i; 
      dum = 1.0 - xest + xest*xest*xest; 
      for ( j = 1; j <= NV; j ++ ) {
         dum /= ( xest + 1.0 ); 
         yest[j]= dum; 
      }
      nrc_pzextr ( iest, xest, yest, yz, dy, NV ); 
      printf ( "\ni = %2d", i ); 
      printf ( "\nExtrap. function:" ); 
      for ( j = 1; j <= NV; j ++ ) printf ( "%12.6f", yz[j] ); 
      printf ( "\nEstimated error: " ); 
      for ( j = 1; j <= NV; j ++ ) printf ( "%12.6f", dy[j] ); 
      printf ( "\n" ); 
   }
   printf ( "\nactual values: %14.6f %11.6f %11.6f %11.6f\n", 
      1.0, 1.0, 1.0, 1.0 ); 
   nrc_free_matrix ( d, 1, IMAXX, 1, IMAXX ); 
   nrc_free_vector ( x, 1, IMAXX ); 
   nrc_free_vector ( yz, 1, NV ); 
   nrc_free_vector ( yest, 1, NV ); 
   nrc_free_vector ( dy, 1, NV ); 
   return 0; 
}
#undef NRANSI
