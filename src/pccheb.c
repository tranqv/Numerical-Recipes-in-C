
#include "nrc_types.h"

void nrc_pccheb ( sReal d[], sReal c[], int n )
{
   int j, jm, jp, k; 
   sReal fac, pow; 

   pow = 1.0; 
   c[0]= 2.0*d[0]; 
   for ( k = 1; k < n; k ++ ) {
      c[k]= 0.0; 
      fac = d[k]/pow; 
      jm = k; 
      jp = 1; 
      for ( j = k; j >= 0; j -= 2, jm --, jp ++ ) {
         c[j] += fac; 
         fac *= ( ( sReal ) jm )/( ( sReal ) jp ); 
      }
      pow += pow; 
   }
}
