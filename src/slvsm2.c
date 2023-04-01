
#include "nrc_types.h"

#include <math.h>

void nrc_slvsm2 ( dReal **u, dReal **rhs )
{
   void nrc_fill0 ( dReal **u, int n ); 
   dReal disc, fact, h = 0.5; 

   nrc_fill0 ( u, 3 ); 
   fact = 2.0/( h*h ); 
   disc = sqrt ( fact*fact + rhs[2][2] ); 
   u[2][2] = - rhs[2][2]/( fact + disc ); 
}
