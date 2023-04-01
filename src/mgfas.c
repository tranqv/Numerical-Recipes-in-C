
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define NPRE 1
#define NPOST 1
#define ALPHA 0.33
#define NGMAX 15

void nrc_mgfas ( dReal **u, int n, int maxcyc )
{
   dReal nrc_anorm2 ( dReal **a, int n ); 
   void nrc_copy ( dReal **aout, dReal **ain, int n ); 
   void nrc_interp ( dReal **uf, dReal **uc, int nf ); 
   void nrc_lop ( dReal **out, dReal **u, int n ); 
   void nrc_matadd ( dReal **a, dReal **b, dReal **c, int n ); 
   void nrc_matsub ( dReal **a, dReal **b, dReal **c, int n ); 
   void nrc_relax2 ( dReal **u, dReal **rhs, int n ); 
   void nrc_rstrct ( dReal **uc, dReal **uf, int nc ); 
   void nrc_slvsm2 ( dReal **u, dReal **rhs ); 
   unsigned int j, jcycle, jj, jm1, jpost, jpre, nf, ng = 0, ngrid, nn; 
   dReal **irho[NGMAX + 1], **irhs[NGMAX + 1], **itau[NGMAX + 1], 
      **itemp[NGMAX + 1], **iu[NGMAX + 1]; 
   dReal res, trerr; 

   nn = n; 
   while ( nn >>= 1 ) ng ++; 
   if ( n != 1 +( 1L << ng ) ) nrc_error ( "n - 1 must be a power of 2 in nrc_mgfas." ); 
   if ( ng > NGMAX ) nrc_error ( "increase NGMAX in nrc_mglin." ); 
   nn = n/2 + 1; 
   ngrid = ng - 1; 
   irho[ngrid]= nrc_dmatrix ( 1, nn, 1, nn ); 
   nrc_rstrct ( irho[ngrid], u, nn ); 
   while ( nn > 3 ) {
      nn = nn/2 + 1; 
      irho[-- ngrid]= nrc_dmatrix ( 1, nn, 1, nn ); 
      nrc_rstrct ( irho[ngrid], irho[ngrid + 1], nn ); 
   }
   nn = 3; 
   iu[1]= nrc_dmatrix ( 1, nn, 1, nn ); 
   irhs[1]= nrc_dmatrix ( 1, nn, 1, nn ); 
   itau[1]= nrc_dmatrix ( 1, nn, 1, nn ); 
   itemp[1]= nrc_dmatrix ( 1, nn, 1, nn ); 
   nrc_slvsm2 ( iu[1], irho[1] ); 
   nrc_free_dmatrix ( irho[1], 1, nn, 1, nn ); 
   ngrid = ng; 
   for ( j = 2; j <= ngrid; j ++ ) {
      nn = 2*nn - 1; 
      iu[j]= nrc_dmatrix ( 1, nn, 1, nn ); 
      irhs[j]= nrc_dmatrix ( 1, nn, 1, nn ); 
      itau[j]= nrc_dmatrix ( 1, nn, 1, nn ); 
      itemp[j]= nrc_dmatrix ( 1, nn, 1, nn ); 
      nrc_interp ( iu[j], iu[j - 1], nn ); 
      nrc_copy ( irhs[j], ( j != ngrid ? irho[j] : u ), nn ); 
      for ( jcycle = 1; jcycle <= maxcyc; jcycle ++ ) {
      nf = nn; 
         for ( jj = j; jj >= 2; jj -- ) {
            for ( jpre = 1; jpre <= NPRE; jpre ++ )
               nrc_relax2 ( iu[jj], irhs[jj], nf ); 
            nrc_lop ( itemp[jj], iu[jj], nf ); 
            nf = nf/2 + 1; 
            jm1 = jj - 1; 
            nrc_rstrct ( itemp[jm1], itemp[jj], nf ); 
            nrc_rstrct ( iu[jm1], iu[jj], nf ); 
            nrc_lop ( itau[jm1], iu[jm1], nf ); 
            nrc_matsub ( itau[jm1], itemp[jm1], itau[jm1], nf ); 
            if ( jj == j )
               trerr = ALPHA*nrc_anorm2 ( itau[jm1], nf ); 
            nrc_rstrct ( irhs[jm1], irhs[jj], nf ); 
            nrc_matadd ( irhs[jm1], itau[jm1], irhs[jm1], nf ); 
         }
         nrc_slvsm2 ( iu[1], irhs[1] ); 
         nf = 3; 
         for ( jj = 2; jj <= j; jj ++ ) {
         jm1 = jj - 1; 
         nrc_rstrct ( itemp[jm1], iu[jj], nf ); 
         nrc_matsub ( iu[jm1], itemp[jm1], itemp[jm1], nf ); 
         nf = 2*nf - 1; 
         nrc_interp ( itau[jj], itemp[jm1], nf ); 
         nrc_matadd ( iu[jj], itau[jj], iu[jj], nf ); 
         for ( jpost = 1; jpost <= NPOST; jpost ++ )
            nrc_relax2 ( iu[jj], irhs[jj], nf ); 
         }
         nrc_lop ( itemp[j], iu[j], nf ); 
         nrc_matsub ( itemp[j], irhs[j], itemp[j], nf ); 
         res = nrc_anorm2 ( itemp[j], nf ); 
         if ( res < trerr ) break; 
      }
   }
   nrc_copy ( u, iu[ngrid], n ); 
   for ( nn = n, j = ng; j >= 1; j --, nn = nn/2 + 1 ) {
      nrc_free_dmatrix ( itemp[j], 1, nn, 1, nn ); 
      nrc_free_dmatrix ( itau[j], 1, nn, 1, nn ); 
      nrc_free_dmatrix ( irhs[j], 1, nn, 1, nn ); 
      nrc_free_dmatrix ( iu[j], 1, nn, 1, nn ); 
      if ( j != ng && j != 1 ) nrc_free_dmatrix ( irho[j], 1, nn, 1, nn ); 
   }
}
#undef NGMAX
#undef NPRE
#undef NPOST
#undef ALPHA
#undef NRANSI
