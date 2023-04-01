
#include "nrc_types.h"

/* Driver for routine nrc_machar */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

int main ( void )
{
   int ibeta, iexp, irnd, it, machep, maxexp, minexp, negep, ngrd; 
   sReal eps, epsneg, xmax, xmin; 

   nrc_machar ( &ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp, 
      &eps, &epsneg, &xmin, &xmax ); 
   printf ( "ibeta = %d\n", ibeta ); 
   printf ( "it = %d\n", it ); 
   printf ( "irnd = %d\n", irnd ); 
   printf ( "ngrd = %d\n", ngrd ); 
   printf ( "machep = %d\n", machep ); 
   printf ( "negep = %d\n", negep ); 
   printf ( "iexp = %d\n", iexp ); 
   printf ( "minexp = %d\n", minexp ); 
   printf ( "maxexp = %d\n", maxexp ); 
   printf ( "eps = %12.6g\n", eps ); 
   printf ( "epsneg = %12.6g\n", epsneg ); 
   printf ( "xmin = %12.6g\n", xmin ); 
   printf ( "xmax = %12.6g\n", xmax ); 
   return 0; 
}
#undef NRANSI
