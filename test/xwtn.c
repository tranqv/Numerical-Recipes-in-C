
#include "nrc_types.h"

/* Driver for routine nrc_wtn */
#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define EPS 1.0e-06
#define NX 8
#define NY 16

int main ( void )
{
   unsigned long i, j, l, nerror = 0, ntot = NX*NY; 
   sReal *a, *aorg; 
   static unsigned long ndim[]={0, NX, NY}; 

   aorg = nrc_vector ( 1, ntot ); 
   a = nrc_vector ( 1, ntot ); 
   nrc_pwtset ( 12 ); 
   for ( i = 1; i <= NX; i ++ )
      for ( j = 1; j <= NY; j ++ ) {
         l = i +( j - 1 )*NX; 
         aorg[l]= a[l]=( i == j ? - 1.0 : 1.0/sqrt ( fabs ( ( sReal )( i - j ) ) ) ); 
      }
   nrc_wtn ( a, ndim, 2, 1, nrc_pwt ); 
   /* here, one might set the smallest components to zero, encode and transmit
   the remaining components as a compressed form of the "image" */
   nrc_wtn ( a, ndim, 2, - 1, nrc_pwt ); 
   for ( l = 1; l <= ntot; l ++ ) {
      if ( fabs ( aorg[l]- a[l] ) >= EPS ) {
         printf ( "Compare Error at element %ld\n", l ); 
         nerror ++; 
      }
   }
   if ( nerror ) printf ( "Number of comparision errors: %ld\n", nerror ); 
   else printf ( "transform - inverse transform check OK\n" ); 
   nrc_free_vector ( a, 1, ntot ); 
   nrc_free_vector ( aorg, 1, ntot ); 
   return nerror; 
}
#undef NRANSI
