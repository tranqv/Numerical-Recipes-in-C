
#include "nrc_types.h"

void nrc_splie2 ( sReal x1a[], sReal x2a[], sReal **ya, int m, int n, sReal **y2a )
{
   void nrc_spline ( sReal x[], sReal y[], int n, sReal yp1, sReal ypn, sReal y2[] ); 
   int j; 

   for ( j = 1; j <= m; j ++ )
      nrc_spline ( x2a, ya[j], n, 1.0e30, 1.0e30, y2a[j] ); 
}
