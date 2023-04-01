
#include "nrc_types.h"

/* Driver for routine nrc_dfpmin */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

static int nfunc, ndfunc; 

sReal func ( sReal x[] )
{
   sReal x1p2sqr = SQR ( 2.0 + x[1] ); 

   nfunc ++; 
   return 10.0*
      SQR ( SQR ( x[2] )*( 3.0 - x[1] )- SQR ( x[1] )*( 3.0 + x[1] ) )+
      x1p2sqr/( 1.0 + x1p2sqr ); 
}

void dfunc ( sReal x[], sReal df[] )
{
   sReal x1sqr = SQR ( x[1] ), x2sqr = SQR ( x[2] ), x1p2 = x[1]+ 2.0; 
   sReal x1p2sqr = SQR ( x1p2 ); 

   ndfunc ++; 
   df[1]= 20.0*( x2sqr*( 3.0 - x[1] )- x1sqr*( 3.0 + x[1] ) )*( - x2sqr - 6.0*x[1]- 3.0*x1sqr )+
      2.0*x1p2/( 1.0 + x1p2sqr )- 2.0*x1p2*x1p2sqr/SQR ( ( 1.0 + x1p2sqr ) ); 
   df[2]= 40.0*( x2sqr*( 3.0 - x[1] )- x1sqr*( 3.0 + x[1] ) )*x[2]*( 3.0 - x[1] ); 
}

#define NDIM 2
#define GTOL 1.0e-4

int main ( void )
{
   int iter; 
   sReal *p, fret; 

   p = nrc_vector ( 1, NDIM ); 
   printf ( "True minimum is at ( - 2.0, +- 0.89442719 )\n" ); 
   nfunc = ndfunc = 0; 
   p[1]= 0.1; 
   p[2]= 4.2; 
   printf ( "Starting nrc_vector: ( %7.4f, %7.4f )\n", p[1], p[2] ); 
   nrc_dfpmin ( p, NDIM, GTOL, &iter, &fret, func, dfunc ); 
   printf ( "Iterations: %3d\n", iter ); 
   printf ( "Func. evals: %3d\n", nfunc ); 
   printf ( "Deriv. evals: %3d\n", ndfunc ); 
   printf ( "Solution nrc_vector: ( %9.6f, %9.6f )\n", p[1], p[2] ); 
   printf ( "Func. value at solution %14.6g\n", fret ); 
   nrc_free_vector ( p, 1, NDIM ); 
   return 0; 
}
#undef NRANSI
