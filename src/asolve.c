
#include "nrc_types.h"

extern unsigned long ija[]; 
extern dReal sa[]; 

void nrc_asolve ( unsigned long n, dReal b[], dReal x[], int itrnsp )
{
   unsigned long i; 

   for ( i = 1; i <= n; i ++ ) x[i]=( sa[i] != 0.0 ? b[i]/sa[i] : b[i] ); 
}
