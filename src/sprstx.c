
#include "nrc_types.h"

void nrc_sprstx ( sReal sa[], unsigned long ija[], sReal x[], sReal b[], 
   unsigned long n )
{
   void nrc_error ( char error_text[] ); 
   unsigned long i, j, k; 

   if ( ija[1] != n + 2 ) nrc_error ( "mismatched nrc_vector and nrc_matrix in nrc_sprstx" ); 
   for ( i = 1; i <= n; i ++ ) b[i]= sa[i]*x[i]; 
   for ( i = 1; i <= n; i ++ ) {
      for ( k = ija[i]; k <= ija[i + 1]- 1; k ++ ) {
         j = ija[k]; 
         b[j] += sa[k]*x[i]; 
      }
   }
}
