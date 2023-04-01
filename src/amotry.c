
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

sReal nrc_amotry ( sReal **p, sReal y[], sReal psum[], int ndim, 
   sReal ( *funk )( sReal [] ), int ihi, sReal fac )
{
   int j; 
   sReal fac1, fac2, ytry, *ptry; 

   ptry = nrc_vector ( 1, ndim ); 
   fac1 =( 1.0 - fac )/ndim; 
   fac2 = fac1 - fac; 
   for ( j = 1; j <= ndim; j ++ ) ptry[j]= psum[j]*fac1 - p[ihi][j]*fac2; 
   ytry =( *funk )( ptry ); 
   if ( ytry < y[ihi] ) {
      y[ihi]= ytry; 
      for ( j = 1; j <= ndim; j ++ ) {
         psum[j] += ptry[j]- p[ihi][j]; 
         p[ihi][j]= ptry[j]; 
      }
   }
   nrc_free_vector ( ptry, 1, ndim ); 
   return ytry; 
}
#undef NRANSI
