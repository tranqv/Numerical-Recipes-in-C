
#include "nrc_types.h"

/* Driver for routine nrc_fourfs */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define SWAP(a,b) {iswap=(a);(a)=(b);(b)=iswap;}
#define FSWAP(a,b) {flswap=(a);(a)=(b);(b)=flswap;}

#define NX 8
#define NY 32
#define NZ 4
#define NDAT (2*NX*NY*NZ)

#define TEMPFILE1 "frfstmp1"
#define TEMPFILE2 "frfstmp2"
#define TEMPFILE3 "frfstmp3"
#define TEMPFILE4 "frfstmp4"

#if defined ( MSDOS ) || defined ( _MSDOS ) || defined ( _MSDOS_ ) || defined ( __MSDOS__ )
#define BINREADWRITE "wb+"
#else
#define BINREADWRITE "w+"
#endif

char *fnames[4]={TEMPFILE1, TEMPFILE2, TEMPFILE3, TEMPFILE4}; 

int main ( void )
{
   int cc, nnv = 3, nwrite; 
   long idum =( - 23 ); 
   unsigned long dim[4], i, j, k, l, ll, iswap; 
   sReal diff, smax, sum, sum1 = 0.0, sum2 = 0.0, tot, *data1, *data2, *data1p, *data2p; 
   FILE *flswap, *file[5]; 

   data1 = nrc_vector ( 1, NDAT ); 
   data2 = nrc_vector ( 1, NDAT ); 
   dim[1]= NX; 
   dim[2]= NY; 
   dim[3]= NZ; 
   tot =( sReal ) NX*( sReal ) NY*( sReal ) NZ; 
   for ( j = 1; j <= 4; j ++ )
      if ( ( file[j]= fopen ( fnames[j - 1], BINREADWRITE ) ) == NULL )
         nrc_error ( "Couldn't open temporary file" ); 
   for ( i = 1; i <= dim[3]; i ++ )
      for ( j = 1; j <= dim[2]; j ++ )
         for ( k = 1; k <= dim[1]; k ++ ) {
            l = k +( j - 1 )*dim[1]+( i - 1 )*dim[2]*dim[1]; 
            l =( l << 1 )- 1; 
            data2[l]= data1[l]= 2*nrc_ran1 ( &idum )- 1; 
            l ++; 
            data2[l]= data1[l]= 2*nrc_ran1 ( &idum )- 1; 
         }
   nwrite = NDAT >> 1; 
   cc = fwrite ( &data1[1], sizeof ( sReal ), nwrite, file[1] ); 
   if ( cc != nwrite ) nrc_error ( "write error in xfourfs" ); 
   cc = fwrite ( &data1[nwrite+1], sizeof ( sReal ), nwrite, file[2] ); 
   if ( cc != nwrite ) nrc_error ( "write error in xfourfs" ); 
   rewind ( file[1] ); 
   rewind ( file[2] ); 
   printf ( "**************** now doing nrc_fourfs *********\n" ); 
   nrc_fourfs ( file, dim, nnv, 1 ); 
   for ( j = 1; j <= 4; j ++ ) rewind ( file[j] ); 
   cc = fread ( &data1[1], sizeof ( sReal ), nwrite, file[3] ); 
   if ( cc != nwrite ) nrc_error ( "read error in xfourfs" ); 
   cc = fread ( &data1[nwrite+1], sizeof ( sReal ), nwrite, file[4] ); 
   if ( cc != nwrite ) nrc_error ( "read error in xfourfs" ); 
   printf ( "**************** now doing nrc_fourn *********\n" ); 
   nrc_fourn ( data2, dim, nnv, 1 ); 
   sum = smax = 0.0; 
   for ( i = 1; i <= dim[3]; i ++ )
      for ( j = 1; j <= dim[2]; j ++ )
         for ( k = 1; k <= dim[1]; k ++ ) {
            l = k +( j - 1 )*dim[1]+( i - 1 )*dim[2]*dim[1]; 
            l =( l << 1 )- 1; 
            ll = i +( j - 1 )*dim[3]+( k - 1 )*dim[3]*dim[2]; 
            ll =( ll << 1 )- 1; 
            diff = sqrt ( SQR ( data2[ll]- data1[l] )+ SQR ( data2[ll + 1]- data1[l + 1] ) ); 
            sum2 += SQR ( data1[l] )+ SQR ( data1[l + 1] ); 
            sum += diff; 
            if ( diff > smax ) smax = diff; 
         }
   sum2 = sqrt ( sum2/tot ); 
   sum = sum/tot; 
   printf ( "( r.m.s. ) value, ( max, ave ) discrepancy = %12.7f %12.7f %12.7f\n", 
      sum2, smax, sum ); 
   /* now check the inverse transforms */
   SWAP ( dim[1], dim[3] ); 
   /* This step swap step is conceptually a reversal, but for
   three dimensions a swap accomplishes that. */
   FSWAP ( file[1], file[3] )
   FSWAP ( file[4], file[2] )
   for ( j = 1; j <= 4; j ++ ) rewind ( file[j] ); 
   printf ( "**************** now doing nrc_fourfs *********\n" ); 
   nrc_fourfs ( file, dim, nnv, - 1 ); 
   for ( j = 1; j <= 4; j ++ ) rewind ( file[j] ); 
   cc = fread ( &data1[1], sizeof ( sReal ), nwrite, file[3] ); 
   if ( cc != nwrite ) nrc_error ( "read error in xfourfs" ); 
   cc = fread ( &data1[nwrite+1], sizeof ( sReal ), nwrite, file[4] ); 
   if ( cc != nwrite ) nrc_error ( "read error in xfourfs" ); 
   SWAP ( dim[1], dim[3] ); 
   printf ( "**************** now doing nrc_fourn *********\n" ); 
   nrc_fourn ( data2, dim, nnv, - 1 ); 
   sum = smax = 0.0; 
   data1p = data1; 
   data2p = data2; 
   for ( j = 1; j <= NDAT; j += 2 ) {
      sum1 += SQR ( data2p[1] )+ SQR ( data2p[2] ); 
      diff = sqrt ( SQR ( data2p[1]- data1p[1] )+ SQR ( data2p[2]- data1p[2] ) ); 
      sum += diff; 
      if ( diff > smax ) smax = diff; 
      data1p += 2; 
      data2p += 2; 
   }
   sum = sum/tot; 
   sum1 = sqrt ( sum1/tot ); 
   printf ( "( r.m.s. ) value, ( max, ave ) discrepancy = %12.7f %12.7f %12.7f\n", 
      sum1, smax, sum ); 
   printf ( "ratio of r.m.s. values, expected ratio = %12.6f %12.6f\n", 
      sum1/sum2, sqrt ( tot ) ); 
   for ( j = 1; j <= 4; j ++ )
      if ( fclose ( file[j] ) == EOF ) nrc_error ( "Couldn't close temporary file" ); 
   nrc_free_vector ( data2, 1, NDAT ); 
   nrc_free_vector ( data1, 1, NDAT ); 
   for ( j = 1; j <= 4; j ++ )
      if ( remove ( fnames[j - 1] ) ) nrc_error ( "Couldn't delete temporary file" ); 
   return 0; 
}
#undef NRANSI
