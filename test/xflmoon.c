
#include "nrc_types.h"

/* Driver for routine nrc_flmoon */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define ZON (-5.0)

int main ( void )
{
   int i, i1, i2, i3, id, im, iy, n, nph = 2; 
   sReal timzon = ZON/24.0, frac, secs; 
   long j1, j2; 
   static char *phase[]={"new moon", "first quarter", 
      "full moon", "last quarter"}; 

   printf ( "Date of the next few phases of the moon\n" ); 
   printf ( "Enter today\'s date ( e.g. 12 15 1992 ) :  \n" ); 
   scanf ( "%d %d %d", &im, &id, &iy ); 
   /* Approximate number of full moons since january 1900 */
   n =( int )( 12.37*( iy - 1900 +( ( im - 0.5 )/12.0 ) ) ); 
   j1 = nrc_julday ( im, id, iy ); 
   nrc_flmoon ( n, nph, &j2, &frac ); 
   n += ( int ) ( ( j1 - j2 )/29.53 + ( j1 >= j2 ? 0.5 : - 0.5 ) ); 
   printf ( "\n%10s %19s %9s\n", "date", "time ( EST )", "phase" ); 
   for ( i = 1; i <= 20; i ++ ) {
      nrc_flmoon ( n, nph, &j2, &frac ); 
      frac = 24.0*( frac + timzon ); 
      if ( frac < 0.0 ) {
         -- j2; 
         frac += 24.0; 
      }
      if ( frac > 12.0 ) {
         ++ j2; 
         frac -= 12.0; 
      } else
         frac += 12.0; 
      i1 =( int ) frac; 
      secs = 3600.0*( frac - i1 ); 
      i2 =( int ) ( secs/60.0 ); 
      i3 =( int ) ( secs - 60*i2 + 0.5 ); 
      nrc_caldat ( j2, &im, &id, &iy ); 
      printf ( "%5d %3d %5d %7d:%2d:%2d %s\n", 
         im, id, iy, i1, i2, i3, phase[nph] ); 
      if ( nph == 3 ) {
         nph = 0; 
         ++ n; 
      } else
         ++ nph; 
   }
   return 0; 
}
#undef NRANSI
