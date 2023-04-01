
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_sort3 ( unsigned long n, sReal ra[], sReal rb[], sReal nrc_rc[] )
{
   void nrc_indexx ( unsigned long n, sReal arr[], unsigned long indx[] ); 
   unsigned long j, *iwksp; 
   sReal *wksp; 

   iwksp = nrc_lvector ( 1, n ); 
   wksp = nrc_vector ( 1, n ); 
   nrc_indexx ( n, ra, iwksp ); 
   for ( j = 1; j <= n; j ++ ) wksp[j]= ra[j]; 
   for ( j = 1; j <= n; j ++ ) ra[j]= wksp[iwksp[j]]; 
   for ( j = 1; j <= n; j ++ ) wksp[j]= rb[j]; 
   for ( j = 1; j <= n; j ++ ) rb[j]= wksp[iwksp[j]]; 
   for ( j = 1; j <= n; j ++ ) wksp[j]= nrc_rc[j]; 
   for ( j = 1; j <= n; j ++ ) nrc_rc[j]= wksp[iwksp[j]]; 
   nrc_free_vector ( wksp, 1, n ); 
   nrc_free_lvector ( iwksp, 1, n ); 
}
#undef NRANSI
