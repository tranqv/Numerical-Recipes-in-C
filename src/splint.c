
#include "nrc_types.h"

void nrc_splint ( sReal xa[], sReal ya[], sReal y2a[], int n, sReal x, sReal *y )
{
   void nrc_error ( char error_text[] ); 
   int klo, khi, k; 
   sReal h, b, a; 

   klo = 1; 
   khi = n; 
   while ( khi - klo > 1 ) {
      k =( khi + klo ) >> 1; 
      if ( xa[k] > x ) khi = k; 
      else klo = k; 
   }
   h = xa[khi]- xa[klo]; 
   if ( h == 0.0 ) nrc_error ( "Bad xa input to routine nrc_splint" ); 
   a =( xa[khi]- x )/h; 
   b =( x - xa[klo] )/h; 
   *y = a*ya[klo]+ b*ya[khi]+( ( a*a*a - a )*y2a[klo]+( b*b*b - b )*y2a[khi] )*( h*h )/6.0; 
}
