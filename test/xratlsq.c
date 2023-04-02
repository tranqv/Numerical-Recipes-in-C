
#include "nrc_types.h"

/* Driver for routine nrc_ratlsq */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NMAX 100

dReal fn ( dReal t )
{
   return atan ( t ); 
}

int main ( void )
{
   int j, kk, mm; 
   dReal a, b, *cof, dev, eee, nrc_fit, xs; 

   cof = nrc_dvector ( 0, NMAX ); 
   for ( ; ; ) {
      printf ( "enter a, b, mm, kk\n" ); 
      if ( scanf ( "%lf %lf %d %d", &a, &b, &mm, &kk ) == EOF ) break; 
      nrc_ratlsq ( fn, a, b, mm, kk, cof, &dev ); 
      for ( j = 0; j <= mm + kk; j ++ ) printf ( "cof ( %3d )=%27.15e\n", j, cof[j] ); 
      printf ( "maximum absolute deviation = %12.6f\n", dev ); 
      printf ( "    x error exact\n" ); 
      printf ( "--------- ------------ ---------\n" ); 
      for ( j = 1; j <= 50; j ++ ) {
         xs = a +( b - a )*( j - 1.0 )/49.0; 
         nrc_fit = nrc_ratval ( xs, cof, mm, kk ); 
         eee = fn ( xs ); 
         printf ( "%10.5f %15.7e %15.7e\n", xs, nrc_fit - eee, eee ); 
      }
   }
   nrc_free_dvector ( cof, 0, NMAX ); 
   return 0; 
}
#undef NRANSI
