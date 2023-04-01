
#include "nrc_types.h"

static sReal xsav, ysav; 
static sReal ( *nrfunc )( sReal, sReal, sReal ); 

sReal nrc_quad3d ( sReal ( *func )( sReal, sReal, sReal ), sReal x1, sReal x2 )
{
   sReal nrc_qgaus ( sReal ( *func )( sReal ), sReal a, sReal b ); 
   sReal nrc_f1 ( sReal x ); 

   nrfunc = func; 
   return nrc_qgaus ( nrc_f1, x1, x2 ); 
}

sReal nrc_f1 ( sReal x )
{
   sReal nrc_qgaus ( sReal ( *func )( sReal ), sReal a, sReal b ); 
   sReal nrc_f2 ( sReal y ); 
   sReal yy1 ( sReal ), yy2 ( sReal ); 

   xsav = x; 
   return nrc_qgaus ( nrc_f2, yy1 ( x ), yy2 ( x ) ); 
}

sReal nrc_f2 ( sReal y )
{
   sReal nrc_qgaus ( sReal ( *func )( sReal ), sReal a, sReal b ); 
   sReal nrc_f3 ( sReal z ); 
   sReal z1 ( sReal, sReal ), z2 ( sReal, sReal ); 

   ysav = y; 
   return nrc_qgaus ( nrc_f3, z1 ( xsav, y ), z2 ( xsav, y ) ); 
}

sReal nrc_f3 ( sReal z )
{
   return ( *nrfunc )( xsav, ysav, z ); 
}
