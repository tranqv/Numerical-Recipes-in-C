
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define NPRE 1
#define NPOST 1
#define NGMAX 15

void nrc_mglin ( dReal **u, int n, int ncycle )
{
   void nrc_addint ( dReal **uf, dReal **uc, dReal **res, int nf ); 
   void nrc_copy ( dReal **aout, dReal **ain, int n ); 
   void nrc_fill0 ( dReal **u, int n ); 
   void nrc_interp ( dReal **uf, dReal **uc, int nf ); 
   void nrc_relax ( dReal **u, dReal **rhs, int n ); 
   void nrc_resid ( dReal **res, dReal **u, dReal **rhs, int n ); 
   void nrc_rstrct ( dReal **uc, dReal **uf, int nc ); 
   void nrc_slvsml ( dReal **u, dReal **rhs ); 
   unsigned int j, jcycle, jj, jpost, jpre, nf, ng = 0, ngrid, nn; 
   dReal **ires[NGMAX + 1], **irho[NGMAX + 1], **irhs[NGMAX + 1], **iu[NGMAX + 1]; 

   nn = n; 
   while ( nn >>= 1 ) ng ++; 
   if ( n != 1 +( 1L << ng ) ) nrc_error ( "n - 1 must be a power of 2 in nrc_mglin." ); 
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
   nrc_slvsml ( iu[1], irho[1] ); 
   nrc_free_dmatrix ( irho[1], 1, nn, 1, nn ); 
   ngrid = ng; 
   for ( j = 2; j <= ngrid; j ++ ) {
      nn = 2*nn - 1; 
      iu[j]= nrc_dmatrix ( 1, nn, 1, nn ); 
      irhs[j]= nrc_dmatrix ( 1, nn, 1, nn ); 
      ires[j]= nrc_dmatrix ( 1, nn, 1, nn ); 
      nrc_interp ( iu[j], iu[j - 1], nn ); 
      nrc_copy ( irhs[j], ( j != ngrid ? irho[j] : u ), nn ); 
      for ( jcycle = 1; jcycle <= ncycle; jcycle ++ ) {
         nf = nn; 
         for ( jj = j; jj >= 2; jj -- ) {
         for ( jpre = 1; jpre <= NPRE; jpre ++ )
            nrc_relax ( iu[jj], irhs[jj], nf ); 
         nrc_resid ( ires[jj], iu[jj], irhs[jj], nf ); 
         nf = nf/2 + 1; 
         nrc_rstrct ( irhs[jj - 1], ires[jj], nf ); 
         nrc_fill0 ( iu[jj - 1], nf ); 
         }
         nrc_slvsml ( iu[1], irhs[1] ); 
         nf = 3; 
         for ( jj = 2; jj <= j; jj ++ ) {
         nf = 2*nf - 1; 
         nrc_addint ( iu[jj], iu[jj - 1], ires[jj], nf ); 
         for ( jpost = 1; jpost <= NPOST; jpost ++ )
            nrc_relax ( iu[jj], irhs[jj], nf ); 
         }
      }
   }
   nrc_copy ( u, iu[ngrid], n ); 
   for ( nn = n, j = ng; j >= 2; j --, nn = nn/2 + 1 ) {
      nrc_free_dmatrix ( ires[j], 1, nn, 1, nn ); 
      nrc_free_dmatrix ( irhs[j], 1, nn, 1, nn ); 
      nrc_free_dmatrix ( iu[j], 1, nn, 1, nn ); 
      if ( j != ng ) nrc_free_dmatrix ( irho[j], 1, nn, 1, nn ); 
   }
   nrc_free_dmatrix ( irhs[1], 1, 3, 1, 3 ); 
   nrc_free_dmatrix ( iu[1], 1, 3, 1, 3 ); 
}
#undef NPRE
#undef NPOST
#undef NGMAX
#undef NRANSI
