
#include "nrc_types.h"

/* Driver for routine nrc_scrsho */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

static sReal fx ( sReal x )
{
   return nrc_bessj0 ( x ); 
}

int main ( void )
{
   nrc_scrsho ( fx ); 
   return 0; 
}
#undef NRANSI
