
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_splin2 ( sReal x1a[], sReal x2a[], sReal **ya, sReal **y2a, int m, int n, 
   sReal x1, sReal x2, sReal *y )
{
   void nrc_spline ( sReal x[], sReal y[], int n, sReal yp1, sReal ypn, sReal y2[] ); 
   void nrc_splint ( sReal xa[], sReal ya[], sReal y2a[], int n, sReal x, sReal *y ); 
   int j; 
   sReal *ytmp, *yytmp; 

   ytmp = nrc_vector ( 1, m ); 
   yytmp = nrc_vector ( 1, m ); 
   for ( j = 1; j <= m; j ++ )
      nrc_splint ( x2a, ya[j], y2a[j], n, x2, &yytmp[j] ); 
   nrc_spline ( x1a, yytmp, m, 1.0e30, 1.0e30, ytmp ); 
   nrc_splint ( x1a, yytmp, ytmp, m, x1, y ); 
   nrc_free_vector ( yytmp, 1, m ); 
   nrc_free_vector ( ytmp, 1, m ); 
}
#undef NRANSI
