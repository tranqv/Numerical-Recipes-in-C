
#include "nrc_types.h"

/* Driver for routine nrc_zbrak */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 100
#define NBMAX 20
#define X1 1.0
#define X2 50.0

static sReal fx ( sReal x )
{
   return nrc_bessj0 ( x ); 
}

int main ( void )
{
   int i, nb = NBMAX; 
   sReal *xb1, *xb2; 

   xb1 = nrc_vector ( 1, NBMAX ); 
   xb2 = nrc_vector ( 1, NBMAX ); 
   nrc_zbrak ( fx, X1, X2, N, xb1, xb2, &nb ); 
   printf ( "\nbrackets for roots of nrc_bessj0:\n" ); 
   printf ( "%21s %10s %16s %10s\n", "lower", "upper", "f ( lower )", "f ( upper )" ); 
   for ( i = 1; i <= nb; i ++ )
      printf ( "%s %2d  %10.4f %10.4f %3s %10.4f %10.4f\n", 
         "  root ", i, xb1[i], xb2[i], " ", 
         fx ( xb1[i] ), fx ( xb2[i] ) ); 
   nrc_free_vector ( xb2, 1, NBMAX ); 
   nrc_free_vector ( xb1, 1, NBMAX ); 
   return 0; 
}
#undef NRANSI
