
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_predic ( sReal data[], int ndata, sReal d[], int m, sReal future[], 
   int nfut )
{
   int k, j; 
   sReal sum, discrp, *reg; 

   reg = nrc_vector ( 1, m ); 
   for ( j = 1; j <= m; j ++ ) reg[j]= data[ndata + 1 - j]; 
   for ( j = 1; j <= nfut; j ++ ) {
      discrp = 0.0; 
      sum = discrp; 
      for ( k = 1; k <= m; k ++ ) sum += d[k]*reg[k]; 
      for ( k = m; k >= 2; k -- ) reg[k]= reg[k - 1]; 
      future[j]= reg[1]= sum; 
   }
   nrc_free_vector ( reg, 1, m ); 
}
#undef NRANSI
