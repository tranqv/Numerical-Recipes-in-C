
#include "nrc_types.h"

/* Driver for routine nrc_four1 */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

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
   ( void ) getchar ( ); 
   return; 
}

#define NN 32
#define NN2 (2*NN)

int main ( void )
{
   long i; 
   int isign; 
   sReal *data, *dcmp; 

   data = nrc_vector ( 1, NN2 ); 
   dcmp = nrc_vector ( 1, NN2 ); 
   printf ( "h ( t )= real - valued even - function\n" ); 
   printf ( "h ( n )= h ( N - n ) and real?\n" ); 
   for ( i = 1; i < NN2; i += 2 ) {
      data[i]= 1.0/( SQR ( ( sReal ) ( i - NN - 1 )/NN )+ 1.0 ); 
      data[i + 1]= 0.0; 
   }
   isign = 1; 
   nrc_four1 ( data, NN, isign ); 
   prntft ( data, NN ); 
   printf ( "h ( t )= imaginary - valued even - function\n" ); 
   printf ( "h ( n )= h ( N - n ) and imaginary?\n" ); 
   for ( i = 1; i < NN2; i += 2 ) {
      data[i + 1]= 1.0/( SQR ( ( sReal ) ( i - NN - 1 )/NN )+ 1.0 ); 
      data[i]= 0.0; 
   }
   isign = 1; 
   nrc_four1 ( data, NN, isign ); 
   prntft ( data, NN ); 
   printf ( "h ( t )= real - valued odd - function\n" ); 
   printf ( "h ( n ) = - h ( N - n ) and imaginary?\n" ); 
   for ( i = 1; i < NN2; i += 2 ) {
      data[i]=( ( sReal ) ( i - NN - 1 )/NN )/( SQR ( ( sReal ) ( i - NN - 1 )/NN )+ 1.0 ); 
      data[i + 1]= 0.0; 
   }
   data[1]= 0.0; 
   isign = 1; 
   nrc_four1 ( data, NN, isign ); 
   prntft ( data, NN ); 
   printf ( "h ( t )= imaginary - valued odd - function\n" ); 
   printf ( "h ( n ) = - h ( N - n ) and real?\n" ); 
   for ( i = 1; i < NN2; i += 2 ) {
      data[i + 1]=( ( sReal ) ( i - NN - 1 )/NN )/( SQR ( ( sReal ) ( i - NN - 1 )/NN )+ 1.0 ); 
      data[i]= 0.0; 
   }
   data[2]= 0.0; 
   isign = 1; 
   nrc_four1 ( data, NN, isign ); 
   prntft ( data, NN ); 
   /* transform, inverse - transform test */
   for ( i = 1; i < NN2; i += 2 ) {
      data[i]= 1.0/( SQR ( 0.5*( i - NN - 1.0 )/NN )+ 1.0 ); 
      dcmp[i]= data[i]; 
      data[i + 1]=( 0.25*( i - NN - 1.0 )/NN )*exp ( - SQR ( 0.5*( i - NN - 1 )/NN ) ); 
      dcmp[i + 1]= data[i + 1]; 
   }
   isign = 1; 
   nrc_four1 ( data, NN, isign ); 
   isign = - 1; 
   nrc_four1 ( data, NN, isign ); 
   printf ( "%23s %33s \n", "original data:", "dReal fourier transform:" ); 
   printf ( "\n %3s %15s %12s %12s %12s \n", 
      "k", "real h ( k )", "imag h ( k )", "real h ( k )", "imag h ( k )" ); 
   for ( i = 1; i < NN; i += 2 )
      printf ( "%4lu %14.6f %12.6f %12.6f %12.6f\n", 
         ( i + 1 )/2, dcmp[i], dcmp[i + 1], data[i]/NN, data[i + 1]/NN ); 
   nrc_free_vector ( dcmp, 1, NN2 ); 
   nrc_free_vector ( data, 1, NN2 ); 
   return 0; 
}
#undef NRANSI
