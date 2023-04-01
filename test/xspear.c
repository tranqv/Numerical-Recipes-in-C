
#include "nrc_types.h"

/* Driver for routine nrc_spear */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDAT 20
#define NMON 12
#define MAXSTR 80

int main ( void )
{
   int i, j; 
   sReal d, probd, probrs, rs, zd, *ave, *data1, *data2, *zlat, **rays; 
   char dummy[MAXSTR], txt[MAXSTR], city[NDAT + 1][17], mon[NMON + 1][5]; 
   FILE *fp; 

   ave = nrc_vector ( 1, NDAT ); 
   data1 = nrc_vector ( 1, NDAT ); 
   data2 = nrc_vector ( 1, NDAT ); 
   zlat = nrc_vector ( 1, NDAT ); 
   rays = nrc_matrix ( 1, NDAT, 1, NMON ); 
   if ( ( fp = fopen ( "table2.dat", "r" ) ) == NULL )
      nrc_error ( "Data file table2.dat not found\n" ); 
   fgets ( dummy, MAXSTR, fp ); 
   fgets ( txt, MAXSTR, fp ); 
   fscanf ( fp, "%*15c" ); 
   for ( i = 1; i <= NMON; i ++ ) fscanf ( fp, " %s", mon[i] ); 
   fgets ( dummy, MAXSTR, fp ); 
   fgets ( dummy, MAXSTR, fp ); 
   for ( i = 1; i <= NDAT; i ++ ) {
      fscanf ( fp, "%[^0123456789]", city[i] ); 
      city[i][16]='\0'; 
      for ( j = 1; j <= NMON; j ++ ) fscanf ( fp, "%lf", &rays[i][j] ); 
      fscanf ( fp, "%lf %lf ", &ave[i], &zlat[i] ); 
   }
   fclose ( fp ); 
   printf ( "%s\n", txt ); 
   printf ( "%16s", " " ); 
   for ( i = 1; i <= 12; i ++ ) printf ( "%4s", mon[i] ); 
   printf ( "\n" ); 
   for ( i = 1; i <= NDAT; i ++ ) {
      printf ( "%s", city[i] ); 
      for ( j = 1; j <= 12; j ++ )
         printf ( "%4d", ( int ) ( 0.5 + rays[i][j] ) ); 
      printf ( "\n" ); 
   }
   /* Check temperature correlations between different months */
   printf ( "\nAre sunny summer places also sunny winter places?\n" ); 
   printf ( "Check correlation of sampled U.S. solar radiation\n" ); 
   printf ( "( july with other months )\n\n" ); 
   printf ( "%s %9s %14s %11s %15s %10s\n", "month", "d", 
      "st. dev.", "probd", "spearman - r", "probrs" ); 
   for ( i = 1; i <= NDAT; i ++ ) data1[i]= rays[i][1]; 
   for ( j = 1; j <= 12; j ++ ) {
      for ( i = 1; i <= NDAT; i ++ ) data2[i]= rays[i][j]; 
      nrc_spear ( data1, data2, NDAT, &d, &zd, &probd, &rs, &probrs ); 
      printf ( "%4s %12.2f %12.6f %12.6f %13.6f %12.6f\n", 
         mon[j], d, zd, probd, rs, probrs ); 
   }
   nrc_free_matrix ( rays, 1, NDAT, 1, NMON ); 
   nrc_free_vector ( zlat, 1, NDAT ); 
   nrc_free_vector ( data2, 1, NDAT ); 
   nrc_free_vector ( data1, 1, NDAT ); 
   nrc_free_vector ( ave, 1, NDAT ); 
   return 0; 
}
#undef NRANSI
