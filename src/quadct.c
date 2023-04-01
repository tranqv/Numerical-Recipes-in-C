
#include "nrc_types.h"

void nrc_quadct ( sReal x, sReal y, sReal xx[], sReal yy[], unsigned long nn, 
   sReal *fa, sReal *fb, sReal *fc, sReal *fd )
{
   unsigned long k, na, nb, nc, nd; 
   sReal ff; 
   na = nb = nc = nd = 0; 
   for ( k = 1; k <= nn; k ++ ) {
      if ( yy[k] > y ) {
         xx[k] > x ? ++ na : ++ nb; 
      } else {
         xx[k] > x ? ++ nd : ++ nc; 
      }
   }
   ff = 1.0/nn; 
   *fa = ff*na; 
   *fb = ff*nb; 
   *fc = ff*nc; 
   *fd = ff*nd; 
}
