
#include "nrc_types.h"

#include <stdlib.h>
#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define PFAC 0.1
#define MNPT 15
#define MNBS 60
#define TINY   1.0e-30
#define BIG    1.0e30

static long iran = 0; 

void nrc_miser ( sReal ( *func )( sReal [] ), sReal regn[], int ndim, unsigned long npts, 
   sReal dith, sReal *ave, sReal *var )
{
   void nrc_ranpt ( sReal pt[], sReal regn[], int n ); 
   sReal *regn_temp; 
   unsigned long n, npre, nptl, nptr; 
   int j, jb; 
   sReal avel, varl; 
   sReal fracl, fval; 
   sReal rgl, rgm, rgr, s, sigl, siglb, sigr, sigrb; 
   sReal sum, sumb, summ, summ2; 
   sReal *fmaxl, *fmaxr, *fminl, *fminr; 
   sReal *pt, *rmid; 

   pt = nrc_vector ( 1, ndim ); 
   if ( npts < MNBS ) {
      summ = summ2 = 0.0; 
      for ( n = 1; n <= npts; n ++ ) {
         nrc_ranpt ( pt, regn, ndim ); 
         fval =( *func )( pt ); 
         summ += fval; 
         summ2 += fval * fval; 
      }
      *ave = summ/npts; 
      *var = FMAX ( TINY, ( summ2 - summ*summ/npts )/( npts*npts ) ); 
   }
   else {
      rmid = nrc_vector ( 1, ndim ); 
      npre = LMAX ( ( unsigned long )( npts*PFAC ), MNPT ); 
      fmaxl = nrc_vector ( 1, ndim ); 
      fmaxr = nrc_vector ( 1, ndim ); 
      fminl = nrc_vector ( 1, ndim ); 
      fminr = nrc_vector ( 1, ndim ); 
      for ( j = 1; j <= ndim; j ++ ) {
         iran =( iran*2661 + 36979 ) % 175000; 
         s = SIGN ( dith, ( sReal )( iran - 87500 ) ); 
         rmid[j]=( 0.5 + s )*regn[j]+( 0.5 - s )*regn[ndim + j]; 
         fminl[j]= fminr[j]= BIG; 
         fmaxl[j]= fmaxr[j] = - BIG; 
      }
      for ( n = 1; n <= npre; n ++ ) {
         nrc_ranpt ( pt, regn, ndim ); 
         fval =( *func )( pt ); 
         for ( j = 1; j <= ndim; j ++ ) {
            if ( pt[j]<= rmid[j] ) {
               fminl[j]= FMIN ( fminl[j], fval ); 
               fmaxl[j]= FMAX ( fmaxl[j], fval ); 
            }
            else {
               fminr[j]= FMIN ( fminr[j], fval ); 
               fmaxr[j]= FMAX ( fmaxr[j], fval ); 
            }
         }
      }
      sumb = BIG; 
      jb = 0; 
      siglb = sigrb = 1.0; 
      for ( j = 1; j <= ndim; j ++ ) {
         if ( fmaxl[j] > fminl[j] && fmaxr[j] > fminr[j] ) {
            sigl = FMAX ( TINY, pow ( fmaxl[j]- fminl[j], 2.0/3.0 ) ); 
            sigr = FMAX ( TINY, pow ( fmaxr[j]- fminr[j], 2.0/3.0 ) ); 
            sum = sigl + sigr; 
            if ( sum <= sumb ) {
               sumb = sum; 
               jb = j; 
               siglb = sigl; 
               sigrb = sigr; 
            }
         }
      }
      nrc_free_vector ( fminr, 1, ndim ); 
      nrc_free_vector ( fminl, 1, ndim ); 
      nrc_free_vector ( fmaxr, 1, ndim ); 
      nrc_free_vector ( fmaxl, 1, ndim ); 
      if ( !jb ) jb = 1 +( ndim*iran )/175000; 
      rgl = regn[jb]; 
      rgm = rmid[jb]; 
      rgr = regn[ndim + jb]; 
      fracl = fabs ( ( rgm - rgl )/( rgr - rgl ) ); 
      nptl =( unsigned long )( MNPT +( npts - npre-2*MNPT )*fracl*siglb
         /( fracl*siglb +( 1.0 - fracl )*sigrb ) ); 
      nptr = npts - npre - nptl; 
      regn_temp = nrc_vector ( 1, 2*ndim ); 
      for ( j = 1; j <= ndim; j ++ ) {
         regn_temp[j]= regn[j]; 
         regn_temp[ndim + j]= regn[ndim + j]; 
      }
      regn_temp[ndim + jb]= rmid[jb]; 
      nrc_miser ( func, regn_temp, ndim, nptl, dith, &avel, &varl ); 
      regn_temp[jb]= rmid[jb]; 
      regn_temp[ndim + jb]= regn[ndim + jb]; 
      nrc_miser ( func, regn_temp, ndim, nptr, dith, ave, var ); 
      nrc_free_vector ( regn_temp, 1, 2*ndim ); 
      *ave = fracl*avel +( 1 - fracl )*( *ave ); 
      *var = fracl*fracl*varl +( 1 - fracl )*( 1 - fracl )*( *var ); 
      nrc_free_vector ( rmid, 1, ndim ); 
   }
   nrc_free_vector ( pt, 1, ndim ); 
}
#undef MNPT
#undef MNBS
#undef TINY
#undef BIG
#undef PFAC
#undef NRANSI
