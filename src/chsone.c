
#include "nrc_types.h"

void nrc_chsone ( sReal bins[], sReal ebins[], int nbins, int knstrn, sReal *df, 
   sReal *chsq, sReal *prob )
{
   sReal nrc_gammq ( sReal a, sReal x ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal temp; 

   *df = nbins - knstrn; 
   *chsq = 0.0; 
   for ( j = 1; j <= nbins; j ++ ) {
      if ( ebins[j] <= 0.0 ) nrc_error ( "Bad expected number in nrc_chsone" ); 
      temp = bins[j]- ebins[j]; 
      *chsq += temp*temp/ebins[j]; 
   }
   *prob = nrc_gammq ( 0.5*( *df ), 0.5*( *chsq ) ); 
}
