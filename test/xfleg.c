
#include "nrc_types.h"

/* Driver for routine nrc_fleg */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NVAL 5
#define DX 0.2
#define NPOLY 5

int main ( void )
{
   int i, j; 
   sReal x, *afunc; 

   afunc = nrc_vector ( 1, NPOLY ); 
   printf ( "\n%3s\n", "Legendre polynomials" ); 
   printf ( "%9s %9s %9s %9s %9s\n", "n = 1", "n = 2", "n = 3", "n = 4", "n = 5" ); 
   for ( i = 1; i <= NVAL; i ++ ) {
      x = i*DX; 
      nrc_fleg ( x, afunc, NPOLY ); 
      printf ( "x =%5.2f\n", x ); 
      for ( j = 1; j <= NPOLY; j ++ ) printf ( "%10.4f", afunc[j] ); 
      printf ( "  routine FLEG\n" ); 
      for ( j = 1; j <= NPOLY; j ++ ) printf ( "%10.4f", nrc_plgndr ( j - 1, 0, x ) ); 
      printf ( "  routine PLGNDR\n\n" ); 
   }
   nrc_free_vector ( afunc, 1, NPOLY ); 
   return 0; 
}
#undef NRANSI
