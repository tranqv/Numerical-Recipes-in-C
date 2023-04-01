
#include "nrc_types.h"

/* Driver for routine nrc_savgol */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NMAX 1000
#define NTEST 6

int main ( void )
{
   int i, j, m, nl, np, nr; 
   sReal *c, sum; 
   static int mtest[NTEST + 1]={0, 2, 2, 2, 2, 4, 4}; 
   static int nltest[NTEST + 1]={0, 2, 3, 4, 5, 4, 5}; 
   static int nrtest[NTEST + 1]={0, 2, 1, 0, 5, 4, 5}; 
   static char *ans[NTEST + 1]={"", 
"                      - 0.086  0.343  0.486  0.343 - 0.086", 
"               - 0.143  0.171  0.343  0.371  0.257", 
"         0.086 - 0.143 - 0.086  0.257  0.886", 
" - 0.084  0.021  0.103  0.161  0.196  0.207  0.196  0.161  0.103  0.021 - 0.084", 
"         0.035 - 0.128  0.070  0.315  0.417  0.315  0.070 - 0.128  0.035", 
"  0.042 - 0.105 - 0.023  0.140  0.280  0.333  0.280  0.140 - 0.023 - 0.105  0.042"}; 

   c = nrc_vector ( 1, NMAX ); 
   printf ( "M nl nr\n" ); 
   printf ( "\t\t\tSample Savitzky - Golay Coefficients\n" ); 
   for ( i = 1; i <= NTEST; i ++ ) {
      m = mtest[i]; 
      nl = nltest[i]; 
      nr = nrtest[i]; 
      np = nl + nr + 1; 
      nrc_savgol ( c, np, nl, nr, 0, m ); 
      for ( sum = 0.0, j = 1; j <= np; j ++ ) sum += c[j]; 
      printf ( "%1d %1d %1d\n", m, nl, nr ); 
      for ( j = nl; j < 5; j ++ ) printf ( "%7s", " " ); 
      for ( j = nl + 1; j >= 1; j -- ) printf ( "%7.3f", c[j] ); 
      for ( j = 0; j < nr; j ++ ) printf ( "%7.3f", c[np - j] ); 
      printf ( "\n" ); 
      printf ( "Sum = %7.3f\n", sum ); 
      printf ( "Compare answer:\n%s\n", ans[i] ); 
   }
   nrc_free_vector ( c, 1, NMAX ); 
   return 0; 
}
#undef NRANSI
