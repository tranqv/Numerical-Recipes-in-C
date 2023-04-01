
#include "nrc_types.h"

void nrc_dsprsax ( dReal sa[], unsigned long ija[], dReal x[], dReal b[], unsigned long n )
{
   void nrc_error ( char error_text[] ); 
   unsigned long i, k; 

   if ( ija[1] != n + 2 ) nrc_error ( "nrc_dsprsax: mismatched nrc_vector and nrc_matrix" ); 
   for ( i = 1; i <= n; i ++ ) {
      b[i]= sa[i]*x[i]; 
      for ( k = ija[i]; k <= ija[i + 1]- 1; k ++ ) b[i] += sa[k]*x[ija[k]]; 
   }
}
