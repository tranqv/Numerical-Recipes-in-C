
#include "nrc_types.h"

/* Driver for routine nrc_sncndn */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MAXSTR 80

int main ( void )
{
   char txt[MAXSTR]; 
   int i, nval; 
   sReal em, emmc, uu, val, sn, cn, dn; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Jacobian Elliptic Function", 26 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%4s %8s %16s %13s %15s %18s\n", "mc", "u", "actual", 
      "sn", "sn^2 + cn^2", "( mc )*( sn^2 )+ dn^2" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf", &em, &uu, &val ); 
      emmc = 1.0 - em; 
      nrc_sncndn ( uu, emmc, &sn, &cn, &dn ); 
      printf ( "%5.2f %8.2f %15.5f %15.5f %12.5f %14.5f\n", 
         emmc, uu, val, sn, ( sn*sn + cn*cn ), ( em*sn*sn + dn*dn ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
