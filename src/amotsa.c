
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

extern long idum; 
extern sReal tt; 

sReal nrc_amotsa ( sReal **p, sReal y[], sReal psum[], int ndim, sReal pb[], 
   sReal *yb, sReal ( *funk )( sReal [] ), int ihi, sReal *yhi, sReal fac )
{
   sReal nrc_ran1 ( long *idum ); 
   int j; 
   sReal fac1, fac2, yflu, ytry, *ptry; 

   ptry = nrc_vector ( 1, ndim ); 
   fac1 =( 1.0 - fac )/ndim; 
   fac2 = fac1 - fac; 
   for ( j = 1; j <= ndim; j ++ )
      ptry[j]= psum[j]*fac1 - p[ihi][j]*fac2; 
   ytry =( *funk )( ptry ); 
   if ( ytry <= *yb ) {
      for ( j = 1; j <= ndim; j ++ ) pb[j]= ptry[j]; 
      *yb = ytry; 
   }
   yflu = ytry - tt*log ( nrc_ran1 ( &idum ) ); 
   if ( yflu < *yhi ) {
      y[ihi]= ytry; 
      *yhi = yflu; 
      for ( j = 1; j <= ndim; j ++ ) {
         psum[j] += ptry[j]- p[ihi][j]; 
         p[ihi][j]= ptry[j]; 
      }
   }
   nrc_free_vector ( ptry, 1, ndim ); 
   return yflu; 
}
#undef NRANSI
