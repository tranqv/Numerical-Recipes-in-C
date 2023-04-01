
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

extern int ncom; 
extern sReal *pcom, *xicom, ( *nrfunc )( sReal [] ); 
extern void ( *nrdfun )( sReal [], sReal [] ); 

sReal nrc_df1dim ( sReal x )
{
   int j; 
   sReal df1 = 0.0; 
   sReal *xt, *df; 

   xt = nrc_vector ( 1, ncom ); 
   df = nrc_vector ( 1, ncom ); 
   for ( j = 1; j <= ncom; j ++ ) xt[j]= pcom[j]+ x*xicom[j]; 
   ( *nrdfun )( xt, df ); 
   for ( j = 1; j <= ncom; j ++ ) df1 += df[j]*xicom[j]; 
   nrc_free_vector ( df, 1, ncom ); 
   nrc_free_vector ( xt, 1, ncom ); 
   return df1; 
}
#undef NRANSI
