
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_convlv ( sReal data[], unsigned long n, sReal respns[], unsigned long m, 
   int isign, sReal ans[] )
{
   void nrc_realft ( sReal data[], unsigned long n, int isign ); 
   void nrc_twofft ( sReal data1[], sReal data2[], sReal fft1[], sReal fft2[], 
      unsigned long n ); 
   unsigned long i, no2; 
   sReal dum, mag2, *fft; 

   fft = nrc_vector ( 1, n << 1 ); 
   for ( i = 1; i <=( m - 1 )/2; i ++ )
      respns[n + 1 - i]= respns[m + 1 - i]; 
   for ( i =( m + 3 )/2; i <= n -( m - 1 )/2; i ++ )
      respns[i]= 0.0; 
   nrc_twofft ( data, respns, fft, ans, n ); 
   no2 = n >> 1; 
   for ( i = 2; i <= n + 2; i += 2 ) {
      if ( isign == 1 ) {
         ans[i - 1]=( fft[i - 1]*( dum = ans[i - 1] )- fft[i]*ans[i] )/no2; 
         ans[i]=( fft[i]*dum + fft[i - 1]*ans[i] )/no2; 
      } else if ( isign == - 1 ) {
         if ( ( mag2 = SQR ( ans[i - 1] )+ SQR ( ans[i] ) ) == 0.0 )
            nrc_error ( "Deconvolving at response zero in nrc_convlv" ); 
         ans[i - 1]=( fft[i - 1]*( dum = ans[i - 1] )+ fft[i]*ans[i] )/mag2/no2; 
         ans[i]=( fft[i]*dum - fft[i - 1]*ans[i] )/mag2/no2; 
      } else nrc_error ( "No meaning for isign in nrc_convlv" ); 
   }
   ans[2]= ans[n + 1]; 
   nrc_realft ( ans, n, - 1 ); 
   nrc_free_vector ( fft, 1, n << 1 ); 
}
#undef NRANSI
