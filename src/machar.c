
#include "nrc_types.h"

#include <math.h>
#define CONV(i) ((sReal)(i))

void nrc_machar ( int *ibeta, int *it, int *irnd, int *ngrd, int *machep, int *negep, 
   int *iexp, int *minexp, int *maxexp, sReal *eps, sReal *epsneg, 
   sReal *xmin, sReal *xmax )
{
   int i, itemp, iz, j, k, mx, nxres; 
   sReal a, b, nrc_beta, betah, betain, one, t, temp, temp1, tempa, two, y, z, zero; 

   one = CONV ( 1 ); 
   two = one + one; 
   zero = one - one; 
   a = one; 
   do {
      a += a; 
      temp = a + one; 
      temp1 = temp - a; 
   } while ( temp1 - one == zero ); 
   b = one; 
   do {
      b += b; 
      temp = a + b; 
      itemp =( int )( temp - a ); 
   } while ( itemp == 0 ); 
   *ibeta = itemp; 
   nrc_beta = CONV ( *ibeta ); 
   *it = 0; 
   b = one; 
   do {
      ++( *it ); 
      b *= nrc_beta; 
      temp = b + one; 
      temp1 = temp - b; 
   } while ( temp1 - one == zero ); 
   *irnd = 0; 
   betah = nrc_beta/two; 
   temp = a + betah; 
   if ( temp - a != zero ) *irnd = 1; 
   tempa = a + nrc_beta; 
   temp = tempa + betah; 
   if ( *irnd == 0 && temp - tempa != zero ) *irnd = 2; 
   *negep =( *it )+ 3; 
   betain = one/nrc_beta; 
   a = one; 
   for ( i = 1; i <=( *negep ); i ++ ) a *= betain; 
   b = a; 
   for ( ; ; ) {
      temp = one - a; 
      if ( temp - one != zero ) break; 
      a *= nrc_beta; 
      --( *negep ); 
   }
   *negep = -( *negep ); 
   *epsneg = a; 
   *machep = -( *it )- 3; 
   a = b; 
   for ( ; ; ) {
      temp = one + a; 
      if ( temp - one != zero ) break; 
      a *= nrc_beta; 
      ++( *machep ); 
   }
   *eps = a; 
   *ngrd = 0; 
   temp = one +( *eps ); 
   if ( *irnd == 0 && temp*one - one != zero ) *ngrd = 1; 
   i = 0; 
   k = 1; 
   z = betain; 
   t = one +( *eps ); 
   nxres = 0; 
   for ( ; ; ) {
      y = z; 
      z = y*y; 
      a = z*one; 
      temp = z*t; 
      if ( a + a == zero || fabs ( z ) >= y ) break; 
      temp1 = temp*betain; 
      if ( temp1*nrc_beta == z ) break; 
      ++ i; 
      k += k; 
   }
   if ( *ibeta != 10 ) {
      *iexp = i + 1; 
      mx = k + k; 
   } else {
      *iexp = 2; 
      iz =( *ibeta ); 
      while ( k >= iz ) {
         iz *= *ibeta; 
         ++( *iexp ); 
      }
      mx = iz + iz - 1; 
   }
   for ( ; ; ) {
      *xmin = y; 
      y *= betain; 
      a = y*one; 
      temp = y*t; 
      if ( a + a != zero && fabs ( y ) < *xmin ) {
         ++ k; 
         temp1 = temp*betain; 
         if ( temp1*nrc_beta == y && temp != y ) {
            nxres = 3; 
            *xmin = y; 
            break; 
         }
      }
      else break; 
   }
   *minexp = - k; 
   if ( mx <= k + k - 3 && *ibeta != 10 ) {
      mx += mx; 
      ++( *iexp ); 
   }
   *maxexp = mx +( *minexp ); 
   *irnd += nxres; 
   if ( *irnd >= 2 ) *maxexp -= 2; 
   i =( *maxexp )+( *minexp ); 
   if ( *ibeta == 2 && !i ) --( *maxexp ); 
   if ( i > 20 ) --( *maxexp ); 
   if ( a != y ) *maxexp -= 2; 
   *xmax = one -( *epsneg ); 
   if ( ( *xmax )*one != *xmax ) *xmax = one - nrc_beta*( *epsneg ); 
   *xmax /= ( *xmin*nrc_beta*nrc_beta*nrc_beta ); 
   i =( *maxexp )+( *minexp )+ 3; 
   for ( j = 1; j <= i; j ++ ) {
      if ( *ibeta == 2 ) *xmax += *xmax; 
      else *xmax *= nrc_beta; 
   }
}
#undef CONV
