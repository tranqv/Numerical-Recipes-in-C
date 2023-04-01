
#include "nrc_types.h"

#include <math.h>

dReal nrc_anorm2 ( dReal **a, int n )
{
   int i, j; 
   dReal sum = 0.0; 

   for ( j = 1; j <= n; j ++ )
      for ( i = 1; i <= n; i ++ )
         sum += a[i][j]*a[i][j]; 
   return sqrt ( sum )/n; 
}
