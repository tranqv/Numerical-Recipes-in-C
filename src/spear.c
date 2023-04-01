
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_spear ( sReal data1[], sReal data2[], unsigned long n, sReal *d, sReal *zd, 
   sReal *probd, sReal *rs, sReal *probrs )
{
   sReal nrc_betai ( sReal a, sReal b, sReal x ); 
   void nrc_crank ( unsigned long n, sReal w[], sReal *s ); 
   sReal nrc_erfcc ( sReal x ); 
   void nrc_sort2 ( unsigned long n, sReal arr[], sReal brr[] ); 
   unsigned long j; 
   sReal vard, t, sg, sf, fac, en3n, en, df, aved, *wksp1, *wksp2; 

   wksp1 = nrc_vector ( 1, n ); 
   wksp2 = nrc_vector ( 1, n ); 
   for ( j = 1; j <= n; j ++ ) {
      wksp1[j]= data1[j]; 
      wksp2[j]= data2[j]; 
   }
   nrc_sort2 ( n, wksp1, wksp2 ); 
   nrc_crank ( n, wksp1, &sf ); 
   nrc_sort2 ( n, wksp2, wksp1 ); 
   nrc_crank ( n, wksp2, &sg ); 
   *d = 0.0; 
   for ( j = 1; j <= n; j ++ )
      *d += SQR ( wksp1[j]- wksp2[j] ); 
   en = n; 
   en3n = en*en*en - en; 
   aved = en3n/6.0 -( sf + sg )/12.0; 
   fac =( 1.0 - sf/en3n )*( 1.0 - sg/en3n ); 
   vard =( ( en - 1.0 )*en*en*SQR ( en + 1.0 )/36.0 )*fac; 
   *zd =( *d - aved )/sqrt ( vard ); 
   *probd = nrc_erfcc ( fabs ( *zd )/1.4142136 ); 
   *rs =( 1.0 -( 6.0/en3n )*( *d +( sf + sg )/12.0 ) )/sqrt ( fac ); 
   fac =( *rs + 1.0 )*( 1.0 -( *rs ) ); 
   if ( fac > 0.0 ) {
      t =( *rs )*sqrt ( ( en - 2.0 )/fac ); 
      df = en - 2.0; 
      *probrs = nrc_betai ( 0.5*df, 0.5, df/( df + t*t ) ); 
   } else
      *probrs = 0.0; 
   nrc_free_vector ( wksp2, 1, n ); 
   nrc_free_vector ( wksp1, 1, n ); 
}
#undef NRANSI
