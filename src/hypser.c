
#include "nrc_types.h"

#include "nrc_complex.h"
#define ONE nrc_cmplx(1.0,0.0)

void nrc_hypser ( sComp a, sComp b, sComp c, sComp z, sComp *series, 
   sComp *deriv )
{
   void nrc_error ( char error_text[] ); 
   int n; 
   sComp aa, bb, cc, fac, temp; 

   deriv -> r = 0.0; 
   deriv -> i = 0.0; 
   fac = nrc_cmplx ( 1.0, 0.0 ); 
   temp = fac; 
   aa = a; 
   bb = b; 
   cc = c; 
   for ( n = 1; n <= 1000; n ++ ) {
      fac = nrc_cmul ( fac, nrc_cdiv ( nrc_cmul ( aa, bb ), cc ) ); 
      deriv -> r += fac.r; 
      deriv -> i += fac.i; 
      fac = nrc_cmul ( fac, nrc_rcmul ( 1.0/n, z ) ); 
      *series = nrc_cadd ( temp, fac ); 
      if ( series -> r == temp.r && series -> i == temp.i ) return; 
      temp = *series; 
      aa = nrc_cadd ( aa, ONE ); 
      bb = nrc_cadd ( bb, ONE ); 
      cc = nrc_cadd ( cc, ONE ); 

   }
   nrc_error ( "convergence failure in nrc_hypser" ); 
}
#undef ONE
