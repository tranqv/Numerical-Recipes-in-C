
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_tridag ( sReal a[], sReal b[], sReal c[], sReal r[], sReal u[], 
   unsigned long n )
{
   unsigned long j; 
   sReal bet, *gam; 

   gam = nrc_vector ( 1, n ); 
   if ( b[1] == 0.0 ) nrc_error ( "Error 1 in nrc_tridag" ); 
   u[1]= r[1]/( bet = b[1] ); 
   for ( j = 2; j <= n; j ++ ) {
      gam[j]= c[j - 1]/bet; 
      bet = b[j]- a[j]*gam[j]; 
      if ( bet == 0.0 ) nrc_error ( "Error 2 in nrc_tridag" ); 
      u[j]=( r[j]- a[j]*u[j - 1] )/bet; 
   }
   for ( j =( n - 1 ); j >= 1; j -- )
      u[j] -= gam[j + 1]*u[j + 1]; 
   nrc_free_vector ( gam, 1, n ); 
}
#undef NRANSI
