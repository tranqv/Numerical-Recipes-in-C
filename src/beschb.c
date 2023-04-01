
#include "nrc_types.h"

#define NUSE1 5
#define NUSE2 5

void nrc_beschb ( dReal x, dReal *gam1, dReal *gam2, dReal *gampl, dReal *gammi )
{
   sReal nrc_chebev ( sReal a, sReal b, sReal c[], int m, sReal x ); 
   sReal xx; 
   static sReal c1[] = {
      - 1.142022680371168e0, 6.5165112670737e-3, 
      3.087090173086e-4, - 3.4706269649e-6, 6.9437664e-9, 
      3.67795e-11, - 1.356e-13}; 
   static sReal c2[] = {
      1.843740587300905e0, - 7.68528408447867e-2, 
      1.2719271366546e-3, - 4.9717367042e-6, - 3.31261198e-8, 
      2.423096e-10, - 1.702e-13, - 1.49e-15}; 

   xx = 8.0*x*x - 1.0; 
   *gam1 = nrc_chebev ( - 1.0, 1.0, c1, NUSE1, xx ); 
   *gam2 = nrc_chebev ( - 1.0, 1.0, c2, NUSE2, xx ); 
   *gampl = *gam2 - x*( *gam1 ); 
   *gammi = *gam2 + x*( *gam1 ); 
}
#undef NUSE1
#undef NUSE2
