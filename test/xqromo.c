
#include "nrc_types.h"

/* Driver for routine nrc_qromo */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define X1 0.0
#define X2 1.5707963267948966192313216916397514420986
#define X3 3.1415926
#define AINF 1.0E20
#define PI 3.1415926

static sReal funcl ( sReal x )
{
   return ( sReal ) ( sqrt ( x )/sin ( x ) ); 
}

static sReal funcu ( sReal x )
{
   return ( sReal ) ( sqrt ( PI - x )/sin ( x ) ); 
}

static sReal fncinf ( sReal x )
{

   return ( sReal ) ( sin ( x )/( x*x ) ); 
}

static sReal fncend ( sReal x )
{
   return ( sReal ) ( exp ( - x )/sqrt ( x ) ); 
}

int main ( void )
{
   sReal res1, res2, result; 

   printf ( "\nImproper integrals:\n\n" ); 
   result = nrc_qromo ( funcl, X1, X2, nrc_midsql ); 
   printf ( "Function: sqrt ( x )/sin ( x )       Interval: ( 0, pi/2 )\n" ); 
   printf ( "Using: MIDSQL                  Result: %8.4f\n\n", result ); 
   result = nrc_qromo ( funcu, X2, X3, nrc_midsqu ); 
   printf ( "Function: sqrt ( pi - x )/sin ( x )    Interval: ( pi/2, pi )\n" ); 
   printf ( "Using: MIDSQU                  Result: %8.4f\n\n", result ); 
   result = nrc_qromo ( fncinf, X2, AINF, nrc_midinf ); 
   printf ( "Function: sin ( x )/x**2          Interval: ( pi/2, infty )\n" ); 
   printf ( "Using: MIDINF                  Result: %8.4f\n\n", result ); 
   result = nrc_qromo ( fncinf, - AINF, - X2, nrc_midinf ); 
   printf ( "Function: sin ( x )/x**2          Interval: ( - infty, - pi/2 )\n" ); 
   printf ( "Using: MIDINF                  Result: %8.4f\n\n", result ); 
   res1 = nrc_qromo ( fncend, X1, X2, nrc_midsql ); 
   res2 = nrc_qromo ( fncend, X2, AINF, nrc_midinf ); 
   printf ( "Function: exp ( - x )/sqrt ( x )      Interval: ( 0.0, infty )\n" ); 
   printf ( "Using: MIDSQL, MIDINF           Result: %8.4f\n\n", res1 + res2 ); 
   res2 = nrc_qromo ( fncend, X2, AINF, nrc_midexp ); 
   printf ( "Function: exp ( - x )/sqrt ( x )      Interval: ( 0.0, infty )\n" ); 
   printf ( "Using: MIDSQL, MIDEXP           Result: %8.4f\n\n", res1 + res2 ); 
   return 0; 
}
#undef NRANSI
