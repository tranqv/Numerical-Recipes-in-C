
#include "nrc_types.h"

sReal nrc_ran4 ( long *idum )
{
   void nrc_psdes ( unsigned long *lword, unsigned long *irword ); 
   unsigned long irword, itemp, lword; 
   static long idums = 0; 
#if defined ( vax ) || defined ( _vax_ ) || defined ( __vax__ ) || defined ( VAX )
   static unsigned long jflone = 0x00004080; 
   static unsigned long jflmsk = 0xffff007f; 
#else
   static unsigned long jflone = 0x3f800000; 
   static unsigned long jflmsk = 0x007fffff; 
#endif

   if ( *idum < 0 ) {
      idums = -( *idum ); 
      *idum = 1; 
   }
   irword =( *idum ); 
   lword = idums; 
   nrc_psdes ( &lword, &irword ); 
   itemp = jflone | ( jflmsk & irword ); 
   ++( *idum ); 
   return ( *( sReal * )&itemp )- 1.0; 
}
