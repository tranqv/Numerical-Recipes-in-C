
#include "nrc_types.h"

/* Driver for routine nrc_fixrts */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_complex.h"

#define NPOLES 6
#define NP1 (NPOLES+1)
#define ONE nrc_cmplx(1.0,0.0)
#define TRUE 1

int main ( void )
{
   int i, polish = TRUE; 
   static sReal d[NP1]=
      {0.0, 6.0, - 15.0, 20.0, - 15.0, 6.0, 0.0}; 
   sComp zcoef[NP1], zeros[NP1], z1, z2; 

   /* finding roots of ( z - 1.0 )^6 = 1.0 */
   /* first write roots */
   zcoef[NPOLES]= ONE; 
   for ( i = NPOLES - 1; i >= 0; i -- )
      zcoef[i] = nrc_cmplx ( - d[NPOLES - i], 0.0 ); 
   nrc_zroots ( zcoef, NPOLES, zeros, polish ); 
   printf ( "Roots of ( z - 1.0 )^6 = 1.0\n" ); 
   printf ( "%24s %27s \n", "Root", "( z - 1.0 )^6" ); 
   for ( i = 1; i <= NPOLES; i ++ ) {
      z1 = nrc_csub ( zeros[i], ONE ); 
      z2 = nrc_cmul ( z1, z1 ); 
      z1 = nrc_cmul ( z1, z2 ); 
      z1 = nrc_cmul ( z1, z1 ); 
      printf ( "%6d %12.6f %12.6f %12.6f %12.6f\n", 
         i, zeros[i].r, zeros[i].i, z1.r, z1.i ); 
   }
   /* now fix them to lie within unit circle */
   nrc_fixrts ( d, NPOLES ); 
   /* check results */
   zcoef[NPOLES]= ONE; 
   for ( i = NPOLES - 1; i >= 0; i -- )
      zcoef[i] = nrc_cmplx ( - d[NPOLES - i], 0.0 ); 
   nrc_zroots ( zcoef, NPOLES, zeros, polish ); 
   printf ( "\nRoots reflected in unit circle\n" ); 
   printf ( "%24s %27s \n", "Root", "( z - 1.0 )^6" ); 
   for ( i = 1; i <= NPOLES; i ++ ) {
      z1 = nrc_csub ( zeros[i], ONE ); 
      z2 = nrc_cmul ( z1, z1 ); 
      z1 = nrc_cmul ( z1, z2 ); 
      z1 = nrc_cmul ( z1, z1 ); 
      printf ( "%6d %12.6f %12.6f %12.6f %12.6f\n", 
         i, zeros[i].r, zeros[i].i, z1.r, z1.i ); 
   }
   return 0; 
}
#undef NRANSI
