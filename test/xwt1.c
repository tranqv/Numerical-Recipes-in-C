
#include "nrc_types.h"

/* Driver for routine nrc_wt1 */
#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NMAX 512
#define NCEN 333
#define NWID 33

int main ( void )
{
   unsigned long i, nused; 
   int itest, k; 
   sReal *u, *v, *w, frac, thresh, tmp; 

   u = nrc_vector ( 1, NMAX ); 
   v = nrc_vector ( 1, NMAX ); 
   w = nrc_vector ( 1, NMAX ); 
   for ( ; ; ) {
      printf ( "Enter k ( 4, - 4, 12, or 20 ) and frac ( 0.0 to 1.0 ):\n" ); 
      if ( scanf ( "%d %lf", &k, &frac ) == EOF ) break; 
      frac = FMIN ( 1.0, FMAX ( 0.0, frac ) ); 
      itest =( k == - 4 ? 1 : 0 ); 
      if ( k < 0 ) k = - k; 
      if ( k != 4 && k != 12 && k != 20 ) continue; 
      for ( i = 1; i <= NMAX; i ++ )
         w[i]= v[i]=( i > NCEN - NWID && i < NCEN + NWID ?
            ( ( sReal )( i - NCEN + NWID )*( sReal )( NCEN + NWID - i ) )/( NWID*NWID ) : 0.0 ); 
      if ( !itest ) nrc_pwtset ( k ); 
      nrc_wt1 ( v, NMAX, 1, itest ? nrc_daub4 : nrc_pwt ); 
      for ( i = 1; i <= NMAX; i ++ ) u[i]= fabs ( v[i] ); 
      thresh = nrc_select ( ( int )( ( 1.0 - frac )*NMAX ), NMAX, u ); 
      nused = 0; 
      for ( i = 1; i <= NMAX; i ++ ) {
         if ( fabs ( v[i] ) <= thresh )
            v[i]= 0.0; 
         else
            nused ++; 
      }
      nrc_wt1 ( v, NMAX, - 1, itest ? nrc_daub4 : nrc_pwt ); 
      for ( thresh = 0.0, i = 1; i <= NMAX; i ++ )
         if ( ( tmp = fabs ( v[i]- w[i] ) ) > thresh ) thresh = tmp; 
      printf ( "k, NMAX, nused = %d %d %d\n", k, NMAX, nused ); 
      printf ( "discrepancy = %12.6f\n", thresh ); 
   }
   nrc_free_vector ( w, 1, NMAX ); 
   nrc_free_vector ( v, 1, NMAX ); 
   nrc_free_vector ( u, 1, NMAX ); 
   return 0; 
}
#undef NRANSI
