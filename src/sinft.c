
#include "nrc_types.h"

#include <math.h>

void nrc_sinft ( sReal y[], int n )
{
   void nrc_realft ( sReal data[], unsigned long n, int isign ); 
   int j, n2 = n + 2; 
   sReal sum, y1, y2; 
   dReal theta, wi = 0.0, wr = 1.0, wpi, wpr, wtemp; 

   theta = 3.14159265358979/( dReal ) n; 
   wtemp = sin ( 0.5*theta ); 
   wpr = - 2.0*wtemp*wtemp; 
   wpi = sin ( theta ); 
   y[1]= 0.0; 
   for ( j = 2; j <=( n >> 1 )+ 1; j ++ ) {
      wr =( wtemp = wr )*wpr - wi*wpi + wr; 
      wi = wi*wpr + wtemp*wpi + wi; 
      y1 = wi*( y[j]+ y[n2 - j] ); 
      y2 = 0.5*( y[j]- y[n2 - j] ); 
      y[j]= y1 + y2; 
      y[n2 - j]= y1 - y2; 
   }
   nrc_realft ( y, n, 1 ); 
   y[1]*= 0.5; 
   sum = y[2]= 0.0; 
   for ( j = 1; j <= n - 1; j += 2 ) {
      sum += y[j]; 
      y[j]= y[j + 1]; 
      y[j + 1]= sum; 
   }
}
