
#include "nrc_types.h"

extern unsigned long ija[]; 
extern dReal sa[]; 

void nrc_atimes ( unsigned long n, dReal x[], dReal r[], int itrnsp )
{
   void nrc_dsprsax ( dReal sa[], unsigned long ija[], dReal x[], dReal b[], 
      unsigned long n ); 
   void nrc_dsprstx ( dReal sa[], unsigned long ija[], dReal x[], dReal b[], 
      unsigned long n ); 

   if ( itrnsp ) nrc_dsprstx ( sa, ija, x, r, n ); 
   else nrc_dsprsax ( sa, ija, x, r, n ); 
}
