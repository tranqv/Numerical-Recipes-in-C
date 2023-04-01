
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

extern int nn; 
extern sReal *fvec; 
extern void ( *nrfuncv )( int n, sReal v[], sReal f[] ); 

sReal nrc_fmin ( sReal x[] )
{
   int i; 
   sReal sum; 

   ( *nrfuncv )( nn, x, fvec ); 
   for ( sum = 0.0, i = 1; i <= nn; i ++ ) sum += SQR ( fvec[i] ); 
   return 0.5*sum; 
}
#undef NRANSI
