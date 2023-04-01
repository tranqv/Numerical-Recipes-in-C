
#include "nrc_types.h"

/* Driver for routine nrc_vegas */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

long idum;       /* for ranno */

int ndim;        /* for fxn */
sReal xoff; 

sReal fxn ( sReal pt[], sReal wgt )
{
   int j; 
   sReal ans, sum; 

   for ( sum = 0.0, j = 1; j <= ndim; j ++ ) sum += ( 100.0*SQR ( pt[j]- xoff ) ); 
   ans =( sum < 80.0 ? exp ( - sum ) : 0.0 ); 
   ans *= pow ( 5.64189, ( dReal ) ndim ); 
   return ans; 
}

int main ( void )
{
   int init, itmax, j, ncall, nprn; 
   sReal avgi, chi2a, sd, xoff; 
   sReal *regn; 

   regn = nrc_vector ( 1, 20 ); 
   printf ( "IDUM =\n" ); 
   scanf ( "%ld", &idum ); 
   if ( idum > 0 ) idum = - idum; 
   for ( ; ;  ) {
      printf ( "ENTER NDIM, XOFF, NCALL, ITMAX, NPRN\n" ); 
      if ( scanf ( "%d %f %d %d %d", &ndim, &xoff, &ncall, &itmax, &nprn ) == EOF ) break; 
      avgi = sd = chi2a = 0.0; 
      for ( j = 1; j <= ndim; j ++ ) {
         regn[j]= 0.0; 
         regn[j + ndim]= 1.0; 
      }
      init = - 1; 
      nrc_vegas ( regn, ndim, fxn, init, ncall, itmax, nprn, &avgi, &sd, &chi2a ); 
      printf ( "Number of iterations performed: %d\n", itmax ); 
      printf ( "Integral,  Standard Dev.,  Chi - sq. = %12.6f %12.6f% 12.6f\n", 
         avgi, sd, chi2a ); 
      init = 1; 
      nrc_vegas ( regn, ndim, fxn, init, ncall, itmax, nprn, &avgi, &sd, &chi2a ); 
      printf ( "Additional iterations performed: %d \n", itmax ); 
      printf ( "Integral,  Standard Dev.,  Chi - sq. = %12.6f %12.6f% 12.6f\n", 
         avgi, sd, chi2a ); 
   }
   nrc_free_vector ( regn, 1, 20 ); 
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
