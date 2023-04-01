
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_correl ( sReal data1[], sReal data2[], unsigned long n, sReal ans[] )
{
   void nrc_realft ( sReal data[], unsigned long n, int isign ); 
   void nrc_twofft ( sReal data1[], sReal data2[], sReal fft1[], sReal fft2[], 
      unsigned long n ); 
   unsigned long no2, i; 
   sReal dum, *fft; 

   fft = nrc_vector ( 1, n << 1 ); 
   nrc_twofft ( data1, data2, fft, ans, n ); 
   no2 = n >> 1; 
   for ( i = 2; i <= n + 2; i += 2 ) {
      ans[i - 1]=( fft[i - 1]*( dum = ans[i - 1] )+ fft[i]*ans[i] )/no2; 
      ans[i]=( fft[i]*dum - fft[i - 1]*ans[i] )/no2; 
   }
   ans[2]= ans[n + 1]; 
   nrc_realft ( ans, n, - 1 ); 
   nrc_free_vector ( fft, 1, n << 1 ); 
}
#undef NRANSI
