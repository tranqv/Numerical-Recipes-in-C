
#include "nrc_types.h"

#include <math.h>

sReal nrc_bico ( int n, int k )
{
   sReal nrc_factln ( int n ); 

   return floor ( 0.5 + exp ( nrc_factln ( n )- nrc_factln ( k )- nrc_factln ( n - k ) ) ); 
}
