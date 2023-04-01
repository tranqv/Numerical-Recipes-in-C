
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_bcuint ( sReal y[], sReal y1[], sReal y2[], sReal y12[], sReal x1l, 
   sReal x1u, sReal x2l, sReal x2u, sReal x1, sReal x2, sReal *ansy, 
   sReal *ansy1, sReal *ansy2 )
{
   void nrc_bcucof ( sReal y[], sReal y1[], sReal y2[], sReal y12[], sReal d1, 
      sReal d2, sReal **c ); 
   int i; 
   sReal t, u, d1, d2, **c; 

   c = nrc_matrix ( 1, 4, 1, 4 ); 
   d1 = x1u - x1l; 
   d2 = x2u - x2l; 
   nrc_bcucof ( y, y1, y2, y12, d1, d2, c ); 
   if ( x1u == x1l || x2u == x2l ) nrc_error ( "Bad input in routine nrc_bcuint" ); 
   t =( x1 - x1l )/d1; 
   u =( x2 - x2l )/d2; 
   *ansy =( *ansy2 )=( *ansy1 )= 0.0; 
   for ( i = 4; i >= 1; i -- ) {
      *ansy = t*( *ansy )+( ( c[i][4]*u + c[i][3] )*u + c[i][2] )*u + c[i][1]; 
      *ansy2 = t*( *ansy2 )+( 3.0*c[i][4]*u + 2.0*c[i][3] )*u + c[i][2]; 
      *ansy1 = u*( *ansy1 )+( 3.0*c[4][i]*t + 2.0*c[3][i] )*t + c[2][i]; 
   }
   *ansy1 /= d1; 
   *ansy2 /= d2; 
   nrc_free_matrix ( c, 1, 4, 1, 4 ); 
}
#undef NRANSI
