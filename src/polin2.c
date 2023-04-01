
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_polin2 ( sReal x1a[], sReal x2a[], sReal **ya, int m, int n, sReal x1, 
   sReal x2, sReal *y, sReal *dy )
{
   void nrc_polint ( sReal xa[], sReal ya[], int n, sReal x, sReal *y, sReal *dy ); 
   int j; 
   sReal *ymtmp; 

   ymtmp = nrc_vector ( 1, m ); 
   for ( j = 1; j <= m; j ++ ) {
      nrc_polint ( x2a, ya[j], n, x2, &ymtmp[j], dy ); 
   }
   nrc_polint ( x1a, ymtmp, m, x1, y, dy ); 
   nrc_free_vector ( ymtmp, 1, m ); 
}
#undef NRANSI
