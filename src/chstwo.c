
#include "nrc_types.h"

void nrc_chstwo ( sReal bins1[], sReal bins2[], int nbins, int knstrn, sReal *df, 
   sReal *chsq, sReal *prob )
{
   sReal nrc_gammq ( sReal a, sReal x ); 
   int j; 
   sReal temp; 

   *df = nbins - knstrn; 
   *chsq = 0.0; 
   for ( j = 1; j <= nbins; j ++ )
      if ( bins1[j] == 0.0 && bins2[j] == 0.0 )
         --( *df ); 
      else {
         temp = bins1[j]- bins2[j]; 
         *chsq += temp*temp/( bins1[j]+ bins2[j] ); 
      }
   *prob = nrc_gammq ( 0.5*( *df ), 0.5*( *chsq ) ); 
}
