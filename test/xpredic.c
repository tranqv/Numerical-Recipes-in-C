
#include "nrc_types.h"

/* Driver for routine nrc_predic */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPTS 500
#define NPOLES 10
#define NFUT 20
#define PI 3.1415926

sReal f ( int n, int npts )
{
   return exp ( -( 1.0*n )/npts )*sin ( 2.0*PI*n/50.0 )
      + exp ( -( 2.0*n )/npts )*sin ( 2.2*PI*n/50.0 ); 
}

int main ( void )
{
   int i; 
   sReal dum, *d, *future, *data; 

   d = nrc_vector ( 1, NPOLES ); 
   future = nrc_vector ( 1, NFUT ); 
   data = nrc_vector ( 1, NPTS ); 
   for ( i = 1; i <= NPTS; i ++ )
      data[i]= f ( i, NPTS ); 
   nrc_memcof ( data, NPTS, NPOLES, &dum, d ); 
   nrc_fixrts ( d, NPOLES ); 
   nrc_predic ( data, NPTS, d, NPOLES, future, NFUT ); 
   printf ( "%6s %11s %12s\n", "I", "Actual", "PREDIC" ); 
   for ( i = 1; i <= NFUT; i ++ )
      printf ( "%6d %12.6f %12.6f\n", i, f ( i + NPTS, NPTS ), future[i] ); 
   nrc_free_vector ( data, 1, NPTS ); 
   nrc_free_vector ( future, 1, NFUT ); 
   nrc_free_vector ( d, 1, NPOLES ); 
   return 0; 
}
#undef NRANSI
