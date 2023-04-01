
#include "nrc_types.h"

#define IAZ 48

void nrc_mp2dfr ( unsigned char a[], unsigned char s[], int n, int *m )
{
   void nrc_mplsh ( unsigned char u[], int n ); 
   void nrc_mpsmu ( unsigned char w[], unsigned char u[], int n, int iv ); 
   int j; 

   *m =( int ) ( 2.408*n ); 
   for ( j = 1; j <=( *m ); j ++ ) {
      nrc_mpsmu ( a, a, n, 10 ); 
      s[j]= a[1]+ IAZ; 
      nrc_mplsh ( a, n ); 
   }
}
#undef IAZ
