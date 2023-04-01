
#include "nrc_types.h"

#include <math.h>

sReal nrc_expdev ( long *idum )
{
   sReal nrc_ran1 ( long *idum ); 
   sReal dum; 

   do
      dum = nrc_ran1 ( idum ); 
   while ( dum == 0.0 ); 
   return - log ( dum ); 
}
