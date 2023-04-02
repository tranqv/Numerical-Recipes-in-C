
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

/* I skip this */
   printf ( "\nSKIP!\n" ) ; 
   return 1; 

   nrc_scrsho ( fx ); 
   return 0; 
}
#undef NRANSI
