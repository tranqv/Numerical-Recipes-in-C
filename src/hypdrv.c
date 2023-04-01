
#include "nrc_types.h"

#include "nrc_complex.h"
#define ONE nrc_cmplx(1.0,0.0)

extern sComp aa, bb, cc, z0, dz; 

void nrc_hypdrv ( sReal s, sReal yy[], sReal dyyds[] )
{
   sComp z, y[3], dyds[3]; 

   y[1]= nrc_cmplx ( yy[1], yy[2] ); 
   y[2]= nrc_cmplx ( yy[3], yy[4] ); 
   z = nrc_cadd ( z0, nrc_rcmul ( s, dz ) ); 
   dyds[1]= nrc_cmul ( y[2], dz ); 
   dyds[2]= nrc_cmul ( nrc_csub ( nrc_cmul ( nrc_cmul ( aa, bb ), y[1] ), nrc_cmul ( nrc_csub ( cc, 
      nrc_cmul ( nrc_cadd ( nrc_cadd ( aa, bb ), ONE ), z ) ), y[2] ) ), 
      nrc_cdiv ( dz, nrc_cmul ( z, nrc_csub ( ONE, z ) ) ) ); 
   dyyds[1]= dyds[1].r; 
   dyyds[2]= dyds[1].i; 
   dyyds[3]= dyds[2].r; 
   dyyds[4]= dyds[2].i; 
}
#undef ONE
