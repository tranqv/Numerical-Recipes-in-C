
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define TINY 1.0e-25
#define ITMAX 200

void nrc_powell ( sReal p[], sReal **xi, int n, sReal ftol, int *iter, sReal *fret, 
   sReal ( *func )( sReal [] ) )
{
   void nrc_linmin ( sReal p[], sReal xi[], int n, sReal *fret, 
      sReal ( *func )( sReal [] ) ); 
   int i, ibig, j; 
   sReal del, fp, fptt, t, *pt, *ptt, *xit; 

   pt = nrc_vector ( 1, n ); 
   ptt = nrc_vector ( 1, n ); 
   xit = nrc_vector ( 1, n ); 
   *fret =( *func )( p ); 
   for ( j = 1; j <= n; j ++ ) pt[j]= p[j]; 
   for ( *iter = 1; ; ++( *iter ) ) {
      fp =( *fret ); 
      ibig = 0; 
      del = 0.0; 
      for ( i = 1; i <= n; i ++ ) {
         for ( j = 1; j <= n; j ++ ) xit[j]= xi[j][i]; 
         fptt =( *fret ); 
         nrc_linmin ( p, xit, n, fret, func ); 
         if ( fptt -( *fret ) > del ) {
            del = fptt -( *fret ); 
            ibig = i; 
         }
      }
      if ( 2.0*( fp -( *fret ) ) <= ftol*( fabs ( fp )+ fabs ( *fret ) )+ TINY ) {
         nrc_free_vector ( xit, 1, n ); 
         nrc_free_vector ( ptt, 1, n ); 
         nrc_free_vector ( pt, 1, n ); 
         return; 
      }
      if ( *iter == ITMAX ) nrc_error ( "nrc_powell exceeding maximum iterations." ); 
      for ( j = 1; j <= n; j ++ ) {
         ptt[j]= 2.0*p[j]- pt[j]; 
         xit[j]= p[j]- pt[j]; 
         pt[j]= p[j]; 
      }
      fptt =( *func )( ptt ); 
      if ( fptt < fp ) {
         t = 2.0*( fp - 2.0*( *fret )+ fptt )*SQR ( fp -( *fret )- del )- del*SQR ( fp - fptt ); 
         if ( t < 0.0 ) {
            nrc_linmin ( p, xit, n, fret, func ); 
            for ( j = 1; j <= n; j ++ ) {
               xi[j][ibig]= xi[j][n]; 
               xi[j][n]= xit[j]; 
            }
         }
      }
   }
}
#undef ITMAX
#undef NRANSI
