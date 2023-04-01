
#include "nrc_types.h"

/* Driver for routine nrc_crank */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDAT 20
#define NMON 12
#define MAXSTR 80

int main ( void )
{
   int i, j; 
   sReal *data, *order, *s, **rays; 
   char dummy[MAXSTR], txt[MAXSTR], city[NDAT + 1][17], mon[NMON + 1][5]; 
   FILE *fp; 

   data = nrc_vector ( 1, NDAT ); 
   order = nrc_vector ( 1, NDAT ); 
   s = nrc_vector ( 1, NMON ); 
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
      fgets ( dummy, MAXSTR, fp ); 
   }
   fclose ( fp ); 
   printf ( "%s\n%16s", txt, " " ); 
   for ( i = 1; i <= 12; i ++ ) printf ( " %s", mon[i] ); 
   printf ( "\n" ); 
   for ( i = 1; i <= NDAT; i ++ ) {
      printf ( "%s", city[i] ); 
      for ( j = 1; j <= 12; j ++ )
         printf ( "%4d", ( int ) ( 0.5 + rays[i][j] ) ); 
      printf ( "\n" ); 
   }
   printf ( " press return to continue ...\n" ); 
   getchar (  ); 
   /* Replace solar flux in each column by nrc_rank order */
   for ( j = 1; j <= 12; j ++ ) {
      for ( i = 1; i <= NDAT; i ++ ) {
         data[i]= rays[i][j]; 
         order[i]= i; 
      }
      nrc_sort2 ( NDAT, data, order ); 
      nrc_crank ( NDAT, data, &s[j] ); 
      for ( i = 1; i <= NDAT; i ++ )
         rays[( int ) ( 0.5 + order[i] )][j]= data[i]; 
   }
   printf ( "%16s", " " ); 
   for ( i = 1; i <= 12; i ++ ) printf ( " %s", mon[i] ); 
   printf ( "\n" ); 
   for ( i = 1; i <= NDAT; i ++ ) {
      printf ( "%s", city[i] ); 
      for ( j = 1; j <= 12; j ++ )
         printf ( "%4d", ( int ) ( 0.5 + rays[i][j] ) ); 
      printf ( "\n" ); 
   }
   nrc_free_matrix ( rays, 1, NDAT, 1, NMON ); 
   nrc_free_vector ( s, 1, NMON ); 
   nrc_free_vector ( order, 1, NDAT ); 
   nrc_free_vector ( data, 1, NDAT ); 
   return 0; 
}
#undef NRANSI
