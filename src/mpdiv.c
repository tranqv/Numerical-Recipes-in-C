
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define MACC 6

void nrc_mpdiv ( unsigned char q[], unsigned char r[], unsigned char u[], 
   unsigned char v[], int n, int m )
{
   void nrc_mpinv ( unsigned char u[], unsigned char v[], int n, int m ); 
   void nrc_mpmov ( unsigned char u[], unsigned char v[], int n ); 
   void nrc_mpmul ( unsigned char w[], unsigned char u[], unsigned char v[], int n, 
      int m ); 
   void nrc_mpsad ( unsigned char w[], unsigned char u[], int n, int iv ); 
   void nrc_mpsub ( int *is, unsigned char w[], unsigned char u[], unsigned char v[], 
      int n ); 
   int is; 
   unsigned char *rr, *s; 

   rr = nrc_cvector ( 1, ( n + MACC )<< 1 ); 
   s = nrc_cvector ( 1, ( n + MACC )<< 1 ); 
   nrc_mpinv ( s, v, n + MACC, m ); 
   nrc_mpmul ( rr, s, u, n + MACC, n ); 
   nrc_mpsad ( s, rr, n + MACC - 1, 1 ); 
   nrc_mpmov ( q, &s[2], n - m + 1 ); 
   nrc_mpmul ( rr, q, v, n - m + 1, m ); 
   nrc_mpsub ( &is, &rr[1], u, &rr[1], n ); 
   if ( is ) nrc_error ( "MACC too small in nrc_mpdiv" ); 
   nrc_mpmov ( r, &rr[n - m + 1], m ); 
   nrc_free_cvector ( s, 1, ( n + MACC )<< 1 ); 
   nrc_free_cvector ( rr, 1, ( n + MACC )<< 1 ); 
}
#undef MACC
#undef NRANSI
