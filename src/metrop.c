
#include "nrc_types.h"

#include <math.h>

int nrc_metrop ( sReal de, sReal t )
{
   sReal nrc_ran3 ( long *idum ); 
   static long gljdum = 1; 

   return de < 0.0 || nrc_ran3 ( &gljdum ) < exp ( - de/t ); 
}
