
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

#define NMAX   5000
#define TINY   1.0e-10

#define GET_PSUM \
					for (j=1;j<=ndim;j++) {\
					for (sum=0.0,i=1;i<=mpts;i++) sum += p[i][j];\
					psum[j]=sum;}
#define SWAP(a,b) {swap=(a);(a)=(b);(b)=swap;}

void nrc_amoeba ( sReal **p, sReal y[], int ndim, sReal ftol, 
   sReal ( *funk )( sReal [] ), int *nfunk )
{
   sReal nrc_amotry ( sReal **p, sReal y[], sReal psum[], int ndim, 
      sReal ( *funk )( sReal [] ), int ihi, sReal fac ); 
   int i, ihi, ilo, inhi, j, mpts = ndim + 1; 
   sReal rtol, sum, swap, ysave, ytry, *psum; 

   psum = nrc_vector ( 1, ndim ); 
   *nfunk = 0; 
   GET_PSUM
   for ( ; ; ) {
      ilo = 1; 
      ihi = y[1]> y[2] ? ( inhi = 2, 1 ) : ( inhi = 1, 2 ); 
      for ( i = 1; i <= mpts; i ++ ) {
         if ( y[i] <= y[ilo] ) ilo = i; 
         if ( y[i] > y[ihi] ) {
            inhi = ihi; 
            ihi = i; 
         } else if ( y[i] > y[inhi] && i != ihi ) inhi = i; 
      }
      rtol = 2.0*fabs ( y[ihi]- y[ilo] )/( fabs ( y[ihi] )+ fabs ( y[ilo] )+ TINY ); 
      if ( rtol < ftol ) {
         SWAP ( y[1], y[ilo] )
         for ( i = 1; i <= ndim; i ++ ) SWAP ( p[1][i], p[ilo][i] )
         break; 
      }
      if ( *nfunk >= NMAX ) nrc_error ( "NMAX exceeded" ); 
      *nfunk += 2; 
      ytry = nrc_amotry ( p, y, psum, ndim, funk, ihi, - 1.0 ); 
      if ( ytry <= y[ilo] )
         ytry = nrc_amotry ( p, y, psum, ndim, funk, ihi, 2.0 ); 
      else if ( ytry >= y[inhi] ) {
         ysave = y[ihi]; 
         ytry = nrc_amotry ( p, y, psum, ndim, funk, ihi, 0.5 ); 
         if ( ytry >= ysave ) {
            for ( i = 1; i <= mpts; i ++ ) {
               if ( i != ilo ) {
                  for ( j = 1; j <= ndim; j ++ )
                     p[i][j]= psum[j]= 0.5*( p[i][j]+ p[ilo][j] ); 
                  y[i]=( *funk )( psum ); 
               }
            }
            *nfunk += ndim; 
            GET_PSUM
         }
      } else --( *nfunk ); 
   }
   nrc_free_vector ( psum, 1, ndim ); 
}
#undef SWAP
#undef GET_PSUM
#undef NMAX
#undef NRANSI
