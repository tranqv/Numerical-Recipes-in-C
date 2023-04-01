
#include "nrc_types.h"

/* Driver for routine nrc_twofft */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 32
#define N2 (2*N)
#define PER 8
#define PI 3.1415926

void prntft ( sReal data[], unsigned long nn )
{
   unsigned long n; 

   printf ( "%4s %13s %13s %12s %13s\n", 
      "n", "real ( n )", "imag.( n )", "real ( N - n )", "imag.( N - n )" ); 
   printf ( "   0 %14.6f %12.6f %12.6f %12.6f\n", 
      data[1], data[2], data[1], data[2] ); 
   for ( n = 3; n <= nn + 1; n += 2 ) {
      printf ( "%4lu %14.6f %12.6f %12.6f %12.6f\n", 
         ( ( n - 1 )/2 ), data[n], data[n + 1], 
         data[2*nn + 2 - n], data[2*nn + 3 - n] ); 
   }
   printf ( " press return to continue ...\n" ); 
   ( void ) getchar (  ); 
   return; 
}

int main ( void )
{
   unsigned long i; 
   int isign; 
   sReal *data1, *data2, *fft1, *fft2; 

   data1 = nrc_vector ( 1, N ); 
   data2 = nrc_vector ( 1, N ); 
   fft1 = nrc_vector ( 1, N2 ); 
   fft2 = nrc_vector ( 1, N2 ); 
   for ( i = 1; i <= N; i ++ ) {
      data1[i]= floor ( 0.5 + cos ( i*2.0*PI/PER ) ); 
      data2[i]= floor ( 0.5 + sin ( i*2.0*PI/PER ) ); 
   }
   nrc_twofft ( data1, data2, fft1, fft2, N ); 
   printf ( "Fourier transform of first function:\n" ); 
   prntft ( fft1, N ); 
   printf ( "Fourier transform of second function:\n" ); 
   prntft ( fft2, N ); 
   /* Invert transform */
   isign = - 1; 
   nrc_four1 ( fft1, N, isign ); 
   printf ( "inverted transform  =  first function:\n" ); 
   prntft ( fft1, N ); 
   nrc_four1 ( fft2, N, isign ); 
   printf ( "inverted transform  =  second function:\n" ); 
   prntft ( fft2, N ); 
   nrc_free_vector ( fft2, 1, N2 ); 
   nrc_free_vector ( fft1, 1, N2 ); 
   nrc_free_vector ( data2, 1, N ); 
   nrc_free_vector ( data1, 1, N ); 
   return 0; 
}
#undef NRANSI
