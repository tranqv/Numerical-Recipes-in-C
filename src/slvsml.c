
#include "nrc_types.h"

void nrc_slvsml ( dReal **u, dReal **rhs )
{
   void nrc_fill0 ( dReal **u, int n ); 
   dReal h = 0.5; 

   nrc_fill0 ( u, 3 ); 
   u[2][2] = - h*h*rhs[2][2]/4.0; 
}
