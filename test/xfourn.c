
#include "nrc_types.h"

/* Driver for routine nrc_fourn */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDIM 3
#define NDAT2 1024

int main ( void )
{
   int isign; 
   long idum =( - 23 ); 
   unsigned long i, j, k, l, ndum = 2, *nn; 
   sReal *data1, *data2; 

   nn = nrc_lvector ( 1, NDIM ); 
   data1 = nrc_vector ( 1, NDAT2 ); 
   data2 = nrc_vector ( 1, NDAT2 ); 
   for ( i = 1; i <= NDIM; i ++ ) nn[i]=( ndum <<= 1 ); 
   for ( i = 1; i <= nn[3]; i ++ )
      for ( j = 1; j <= nn[2]; j ++ )
         for ( k = 1; k <= nn[1]; k ++ ) {
            l = k +( j - 1 )*nn[1]+( i - 1 )*nn[2]*nn[1]; 
            l =( l << 1 )- 1; 
            /* real part of component */
            data2[l]= data1[l]= 2*nrc_ran1 ( &idum )- 1; 
            /* imaginary part of component */
            l ++; 
            data2[l]= data1[l]= 2*nrc_ran1 ( &idum )- 1; 
         }
   isign = 1; 
   nrc_fourn ( data2, nn, NDIM, isign ); 
   /* here would be any processing to be done in Fourier space */
   isign = - 1; 
   nrc_fourn ( data2, nn, NDIM, isign ); 
   printf ( "Double 3 - dimensional transform\n\n" ); 
   printf ( "%22s %24s %20s\n", 
      "Double transf.", "Original data", "Ratio" ); 
   printf ( "%10s %13s %12s %13s %11s %13s\n\n", 
      "real", "imag.", "real", "imag.", "real", "imag." ); 
   for ( i = 1; i <= 4; i ++ ) {
      k = 2*( j = 2*i ); 
      l = k +( j - 1 )*nn[1]+( i - 1 )*nn[2]*nn[1]; 
      l =( l << 1 )- 1; 
      printf ( "%12.2f %12.2f %10.2f %12.2f %14.2f %12.2f\n", 
         data2[l], data2[l + 1], data1[l], data1[l + 1], 
         data2[l]/data1[l], data2[l + 1]/data1[l + 1] ); 
   }
   printf ( "\nThe product of transform lengths is: %4lu\n", nn[1]*nn[2]*nn[3] ); 
   nrc_free_vector ( data2, 1, NDAT2 ); 
   nrc_free_vector ( data1, 1, NDAT2 ); 
   nrc_free_lvector ( nn, 1, NDIM ); 
   return 0; 
}
#undef NRANSI
