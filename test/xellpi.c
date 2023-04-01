
#include "nrc_types.h"

/* Driver for routine nrc_ellpi */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MAXSTR 80

#define FAC (3.1415926535/180.0)

int main ( void )
{
   char txt[MAXSTR]; 
   int i, nval; 
   sReal ak, alpha, en, phi, val; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Legendre Elliptic Integral Third Kind", 37 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%6s %6s %6s %10s %23s\n", 
      "phi", "- en", "sin ( alpha )", "actual", "nrc_ellpi ( phi, ak )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf %lf", &phi, &en, &alpha, &val ); 
      alpha = alpha*FAC; 
      ak = sin ( alpha ); 
      en = - en; 
      phi = phi*FAC; 
      printf ( "%6.2f %6.2f %6.2f %18.6e %18.6e\n", 
         phi, en, ak, val, nrc_ellpi ( phi, en, ak ) ); 

   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
