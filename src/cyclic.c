
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_cyclic ( sReal a[], sReal b[], sReal c[], sReal alpha, sReal nrc_beta, 
   sReal r[], sReal x[], unsigned long n )
{
   void nrc_tridag ( sReal a[], sReal b[], sReal c[], sReal r[], sReal u[], 
      unsigned long n ); 
   unsigned long i; 
   sReal fact, gamma, *bb, *u, *z; 

   if ( n <= 2 ) nrc_error ( "n too small in nrc_cyclic" ); 
   bb = nrc_vector ( 1, n ); 
   u = nrc_vector ( 1, n ); 
   z = nrc_vector ( 1, n ); 
   gamma = - b[1]; 
   bb[1]= b[1]- gamma; 
   bb[n]= b[n]- alpha*nrc_beta/gamma; 
   for ( i = 2; i < n; i ++ ) bb[i]= b[i]; 
   nrc_tridag ( a, bb, c, r, x, n ); 
   u[1]= gamma; 
   u[n]= alpha; 
   for ( i = 2; i < n; i ++ ) u[i]= 0.0; 
   nrc_tridag ( a, bb, c, u, z, n ); 
   fact =( x[1]+ nrc_beta*x[n]/gamma )/
      ( 1.0 + z[1]+ nrc_beta*z[n]/gamma ); 
   for ( i = 1; i <= n; i ++ ) x[i] -= fact*z[i]; 
   nrc_free_vector ( z, 1, n ); 
   nrc_free_vector ( u, 1, n ); 
   nrc_free_vector ( bb, 1, n ); 
}
#undef NRANSI
