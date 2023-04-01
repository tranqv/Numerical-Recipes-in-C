
#include "nrc_types.h"

#include <math.h>

sReal nrc_beta ( sReal z, sReal w )
{
   sReal nrc_gammln ( sReal xx ); 

   return exp ( nrc_gammln ( z )+ nrc_gammln ( w )- nrc_gammln ( z + w ) ); 
}
