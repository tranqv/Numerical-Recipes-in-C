#include "nrc_types.h"

#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793238462643383279502884197



int main ( void )
{
   sReal x = PI ; 

   printf ( "%8s%23.16E, %8s%23.16E \n", "PI =", "|-PI| =", PI, fabs(-PI) ) ; 
   printf ( "%8s%23.16E, %8s%23.16E \n", "x  =", "|-x | =",  x, fabs(-x ) ) ; 


   printf ("Size of int: %ld \n", sizeof(int));
   printf ("Size of char: %ld \n", sizeof(char));
   printf ("Size of float: %ld \n", sizeof(float));
   printf ("Size of double: %ld \n", sizeof(double));

   printf ("Size of sReal: %ld \n", sizeof(sReal));
   printf ("Size of dReal: %ld \n", sizeof(dReal));
   printf ("Size of qReal: %ld \n", sizeof(qReal));


   printf ( "%15s = %23.16E \n", "NR_CONST_EPSI", NR_CONST_EPSI  ) ; 
   printf ( "%15s = %23.16E \n", "NR_CONST_TINY", NR_CONST_TINY  ) ; 
   printf ( "%15s = %23.16E \n", "NR_CONST_HUGE", NR_CONST_HUGE  ) ; 
   printf ( "%15s = %23.16E \n", "NR_CONST_FPMIN", NR_CONST_FPMIN  ) ; 

   return 0; 
}

#undef PI




