
#include "nrc_types.h"

/* Driver for routine nrc_zroots */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_complex.h"

#define M 4
#define MP1 (M+1)
#define TRUE 1
#define FALSE 0

int main ( void )
{
   int i, polish; 
   sComp roots[MP1]; 
   static sComp a[MP1]={{0.0, 2.0}, 
            {0.0, 0.0}, 
            {- 1.0, - 2.0}, 
            {0.0, 0.0}, 
            {1.0, 0.0} }; 

   printf ( "\nRoots of the polynomial x^4 -( 1 + 2i )*x^2 + 2i\n" ); 
   polish = FALSE; 
   nrc_zroots ( a, M, roots, polish ); 
   printf ( "\nUnpolished roots:\n" ); 
   printf ( "%14s %13s %13s\n", "root #", "real", "imag." ); 
   for ( i = 1; i <= M; i ++ )
      printf ( "%11d %18.6f %12.6f\n", i, roots[i].r, roots[i].i ); 
   printf ( "\nCorrupted roots:\n" ); 
   for ( i = 1; i <= M; i ++ )
      roots[i]= nrc_rcmul ( 1 + 0.01*i, roots[i] ); 
   printf ( "%14s %13s %13s\n", "root #", "real", "imag." ); 
   for ( i = 1; i <= M; i ++ )
      printf ( "%11d %18.6f %12.6f\n", i, roots[i].r, roots[i].i ); 
   polish = TRUE; 
   nrc_zroots ( a, M, roots, polish ); 
   printf ( "\nPolished roots:\n" ); 
   printf ( "%14s %13s %13s\n", "root #", "real", "imag." ); 
   for ( i = 1; i <= M; i ++ )
      printf ( "%11d %18.6f %12.6f \n", i, roots[i].r, roots[i].i ); 
   return 0; 
}
#undef NRANSI
