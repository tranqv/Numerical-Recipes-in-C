
#include "nrc_types.h"

#include <math.h>

void nrc_fgauss ( sReal x, sReal a[], sReal *y, sReal dyda[], int na )
{
   int i; 
   sReal fac, ex, arg; 

   *y = 0.0; 
   for ( i = 1; i <= na - 1; i += 3 ) {
      arg =( x - a[i + 1] )/a[i + 2]; 
      ex = exp ( - arg*arg ); 
      fac = a[i]*ex*2.0*arg; 
      *y += a[i]*ex; 
      dyda[i]= ex; 
      dyda[i + 1]= fac/a[i + 2]; 
      dyda[i + 2]= fac*arg/a[i + 2]; 
   }
}
