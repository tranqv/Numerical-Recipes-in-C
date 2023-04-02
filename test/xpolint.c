
#include "nrc_types.h"

/* Driver for routine nrc_polint */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define PI 3.1415926

int main ( void )
{
   int i, n, nfunc; 
   sReal dy, f, x, y, *xa, *ya; 

   printf ( "generation of interpolation tables\n" ); 
   printf ( " ... sin ( x ) 0 < x < PI\n" ); 
   printf ( " ... exp ( x ) 0 < x < 1 \n" ); 
   printf ( "how many entries go in these tables?\n" ); 
   if ( scanf ( "%d", &n ) == EOF ) return 1; 
   xa = nrc_vector ( 1, n ); 
   ya = nrc_vector ( 1, n ); 
   for ( nfunc = 1; nfunc <= 2; nfunc ++ ) {
      if ( nfunc == 1 ) {
         printf ( "\nsine function from 0 to PI\n" ); 
         for ( i = 1; i <= n; i ++ ) {
            xa[i]= i*PI/n; 
            ya[i]= sin ( xa[i] ); 
         }
      } else if ( nfunc == 2 ) {
         printf ( "\nexponential function from 0 to 1\n" ); 
         for ( i = 1; i <= n; i ++ ) {
            xa[i]= i*1.0/n; 
            ya[i]= exp ( xa[i] ); 
         }
      } else {
         break; 
      }
      printf ( "\n%9s %13s %16s %13s\n", 
         "x", "f ( x )", "interpolated", "error" ); 
      for ( i = 1; i <= 10; i ++ ) {
         if ( nfunc == 1 ) {
            x =( - 0.05 + i/10.0 )*PI; 
            f = sin ( x ); 
         } else if ( nfunc == 2 ) {
            x =( - 0.05 + i/10.0 ); 
            f = exp ( x ); 
         }
         nrc_polint ( xa, ya, n, x, &y, &dy ); 
         printf ( "%12.6f %12.6f %12.6f %4s %13.6e\n", 
            x, f, y, " ", dy ); 
      }
      printf ( "\n***********************************\n" ); 
      printf ( "press RETURN\n" ); 
      ( void ) getchar ( ); 
   }
   nrc_free_vector ( ya, 1, n ); 
   nrc_free_vector ( xa, 1, n ); 
   return 0; 
}
#undef NRANSI
