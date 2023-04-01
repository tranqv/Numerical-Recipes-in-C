
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#include <limits.h>
#define MC 512
#ifdef ULONG_MAX
#define MAXINT (ULONG_MAX >> 1)
#else
#define MAXINT 2147483647
#endif

typedef struct {
   unsigned long *ilob, *iupb, *ncumfq, jdif, nc, minint, nch, ncum, nrad; 
} arithcode; 

void nrc_arcmak ( unsigned long nfreq[], unsigned long nchh, unsigned long nradd, 
   arithcode *acode )
{
   unsigned long j; 

   if ( nchh > MC ) nrc_error ( "input radix may not exceed MC in nrc_arcmak." ); 
   if ( nradd > 256 ) nrc_error ( "output radix may not exceed 256 in nrc_arcmak." ); 

   acode -> minint = MAXINT/nradd; 
   acode -> nch = nchh; 
   acode -> nrad = nradd; 
   acode -> ncumfq[1]= 0; 
   for ( j = 2; j <= acode -> nch + 1; j ++ )
      acode -> ncumfq[j]= acode -> ncumfq[j - 1]+ IMAX ( nfreq[j - 1], 1 ); 
   acode -> ncum = acode -> ncumfq[acode -> nch + 2]= acode -> ncumfq[acode -> nch + 1]+ 1; 
}
#undef MC
#undef MAXINT
#undef NRANSI
