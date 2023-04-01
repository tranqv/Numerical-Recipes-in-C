
#include "nrc_types.h"

/* Driver for routine nrc_simplx */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 4
#define M 4
#define NP 5        /* NP >= N+1 */
#define MP 6        /* MP >= M+2 */
#define M1 2        /* M1+M2+M3 = M */
#define M2 1
#define M3 1
#define NM1M2 (N+M1+M2)

int main ( void )
{
   int i, icase, j, *izrov, *iposv; 
   static sReal c[MP][NP]=
      {0.0, 1.0, 1.0, 3.0, - 0.5, 
      740.0, - 1.0, 0.0, - 2.0, 0.0, 
      0.0, 0.0, - 2.0, 0.0, 7.0, 
      0.5, 0.0, - 1.0, 1.0, - 2.0, 
      9.0, - 1.0, - 1.0, - 1.0, - 1.0, 
      0.0, 0.0, 0.0, 0.0, 0.0}; 
   sReal **a; 
   static char *txt[NM1M2 + 1]=
      {" ", "x1", "x2", "x3", "x4", "y1", "y2", "y3"}; 

   izrov = nrc_ivector ( 1, N ); 
   iposv = nrc_ivector ( 1, M ); 
   a = nrc_convert_matrix ( &c[0][0], 1, MP, 1, NP ); 
   nrc_simplx ( a, M, N, M1, M2, M3, &icase, izrov, iposv ); 
   if ( icase == 1 )
      printf ( "\nunbounded objective function\n" ); 
   else if ( icase == - 1 )
      printf ( "\nno solutions satisfy constraints given\n" ); 
   else {
      printf ( "\n%11s", " " ); 
      for ( i = 1; i <= N; i ++ )
         if ( izrov[i] <= NM1M2 ) printf ( "%10s", txt[izrov[i]] ); 
      printf ( "\n" ); 
      for ( i = 1; i <= M + 1; i ++ ) {
         if ( i == 1 || iposv[i - 1] <= NM1M2 ) {
            if ( i > 1 )
               printf ( "%s", txt[iposv[i - 1]] ); 
            else
               printf ( "  " ); 
            printf ( "%10.2f", a[i][1] ); 
            for ( j = 2; j <= N + 1; j ++ )
               if ( izrov[j - 1] <= NM1M2 )
                  printf ( "%10.2f", a[i][j] ); 
            printf ( "\n" ); 
         }
      }
   }
   nrc_free_convert_matrix ( a, 1, MP, 1, NP ); 
   nrc_free_ivector ( iposv, 1, M ); 
   nrc_free_ivector ( izrov, 1, N ); 
   return 0; 
}
#undef NRANSI
