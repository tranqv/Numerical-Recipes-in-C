
#include "nrc_types.h"

#include <math.h>

sReal nrc_evlmem ( sReal fdt, sReal d[], int m, sReal xms )
{
   int i; 
   sReal sumr = 1.0, sumi = 0.0; 
   dReal wr = 1.0, wi = 0.0, wpr, wpi, wtemp, theta; 

   theta = 6.28318530717959*fdt; 
   wpr = cos ( theta ); 
   wpi = sin ( theta ); 
   for ( i = 1; i <= m; i ++ ) {
      wr =( wtemp = wr )*wpr - wi*wpi; 
      wi = wi*wpr + wtemp*wpi; 
      sumr -= d[i]*wr; 
      sumi -= d[i]*wi; 
   }
   return xms/( sumr*sumr + sumi*sumi ); 
}
