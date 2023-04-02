
#include "nrc_types.h"

/* Driver for routine nrc_dfridr */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

sReal func ( sReal x )
{
   return tan ( x ); 
}

int main ( void )
{
   sReal x, h, dx, err; 

   printf ( "input x, h\n" ); 
   while ( scanf ( "%lf %lf", &x, &h ) != EOF ) {
      dx = nrc_dfridr ( func, x, h, &err ); 
      printf ( "nrc_dfridr =%12.6f %12.6f %12.6f\n", dx, 1.0/SQR ( cos ( x ) ), err ); 
   }

   return 0; 
}
#undef NRANSI
