

#define _NRC_COMPLEX_


#ifndef _NRC_TYPES_
#define _NRC_TYPES_
#include "nrc_types.h"
#endif


sComp nrc_cadd ( sComp a,  sComp b ); 
sComp nrc_csub ( sComp a,  sComp b ); 
sComp nrc_cmul ( sComp a,  sComp b ); 
sComp nrc_cmplx ( sReal re,  sReal im ); 
sComp nrc_conjg ( sComp z ); 
sComp nrc_cdiv ( sComp a,  sComp b ); 
sReal nrc_cabs ( sComp z ); 
sComp nrc_csqrt ( sComp z ); 
sComp nrc_rcmul ( sReal x,  sComp a ); 

