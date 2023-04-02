
#include "nrc_types.h"

/* Driver for routine nrc_dftint */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

static sReal c, d; 

sReal coscxd ( sReal x )
{
   return cos ( c*x + d ); 
}

#define ci(x) (sin((w-c)*x-d)/(2.0*(w-c))+sin((w+c)*x+d)/(2.0*(w+c)))
#define si(x) (-cos((w-c)*x-d)/(2.0*(w-c))-cos((w+c)*x+d)/(2.0*(w+c)))

void getans ( sReal w, sReal a, sReal b, sReal *cans, sReal *sans )
{
   *cans = ci ( b )- ci ( a ); 
   *sans = si ( b )- si ( a ); 
}

int main ( void )
{
   sReal a, b, cans, cosint, sans, sinint, w; 

   printf ( "  Omega Integral cosine*test func Err" ); 
   printf ( "    Integral sine*test func Err\n" ); 
   for ( ; ; ) {
      printf ( "input c, d:\n" ); 
      if ( scanf ( "%lf %lf", &c, &d ) == EOF ) break; 
      for ( ; ; ) {
         printf ( "input a, b:\n" ); 
         if ( scanf ( "%lf %lf", &a, &b ) == EOF ) break; 
         if ( a == b ) break; 
         for ( ; ; ) {
            printf ( "input w:\n" ); 
            if ( scanf ( "%lf", &w ) == EOF ) break; 
            if ( w < 0.0 ) break; 
            nrc_dftint ( coscxd, a, b, w, &cosint, &sinint ); 
            getans ( w, a, b, &cans, &sans ); 
            printf ( "%15.6e %15.6e %15.6e %15.6e %15.6e\n", 
                  w, cans, cosint - cans, sans, sinint - sans ); 
         }
      }
   }
   printf ( "normal completion\n" ); 
   return 0; 
}
#undef NRANSI
