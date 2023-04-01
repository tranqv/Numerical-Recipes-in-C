
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

extern int ncom; 
extern sReal *pcom, *xicom, ( *nrfunc )( sReal [] ); 

sReal nrc_f1dim ( sReal x )
{
   int j; 
   sReal f, *xt; 

   xt = nrc_vector ( 1, ncom ); 
   for ( j = 1; j <= ncom; j ++ ) xt[j]= pcom[j]+ x*xicom[j]; 
   f =( *nrfunc )( xt ); 
   nrc_free_vector ( xt, 1, ncom ); 
   return f; 
}
#undef NRANSI
