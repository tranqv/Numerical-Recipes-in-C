
#include "nrc_types.h"

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define KBF 128

void nrc_fourfs ( FILE *file[5], unsigned long nn[], int ndim, int isign )
{
   void nrc_fourew ( FILE *file[5], int *na, int *nb, int *nc, int *nd ); 
   unsigned long j, j12, jk, k, kk, n = 1, mm, kc = 0, kd, ks, kr, nr, ns, nv; 
   int cc, na, nb, nc, nd; 
   sReal tempr, tempi, *afa, *afb, *afc; 
   dReal wr, wi, wpr, wpi, wtemp, theta; 
   static int mate[5] = {0, 2, 1, 4, 3}; 

   afa = nrc_vector ( 1, KBF ); 
   afb = nrc_vector ( 1, KBF ); 
   afc = nrc_vector ( 1, KBF ); 
   for ( j = 1; j <= ndim; j ++ ) {
      n *= nn[j]; 
      if ( nn[j] <= 1 ) nrc_error ( "invalid sReal or wrong ndim in nrc_fourfs" ); 
   }
   nv = 1; 
   jk = nn[nv]; 
   mm = n; 
   ns = n/KBF; 
   nr = ns >> 1; 
   kd = KBF >> 1; 
   ks = n; 
   nrc_fourew ( file, &na, &nb, &nc, &nd ); 
   for ( ; ; ) {
      theta = isign*3.141592653589793238462643383279502884197/( n/mm ); 
      wtemp = sin ( 0.5*theta ); 
      wpr = - 2.0*wtemp*wtemp; 
      wpi = sin ( theta ); 
      wr = 1.0; 
      wi = 0.0; 
      mm >>= 1; 
      for ( j12 = 1; j12 <= 2; j12 ++ ) {
         kr = 0; 
         do {
            cc = fread ( &afa[1], sizeof ( sReal ), KBF, file[na] ); 
            if ( cc != KBF ) nrc_error ( "read error in nrc_fourfs" ); 
            cc = fread ( &afb[1], sizeof ( sReal ), KBF, file[nb] ); 
            if ( cc != KBF ) nrc_error ( "read error in nrc_fourfs" ); 
            for ( j = 1; j <= KBF; j += 2 ) {
               tempr =( ( sReal ) wr )*afb[j]-( ( sReal ) wi )*afb[j + 1]; 
               tempi =( ( sReal ) wi )*afb[j]+( ( sReal ) wr )*afb[j + 1]; 
               afb[j]= afa[j]- tempr; 
               afa[j] += tempr; 
               afb[j + 1]= afa[j + 1]- tempi; 
               afa[j + 1] += tempi; 
            }
            kc += kd; 
            if ( kc == mm ) {
               kc = 0; 
               wr =( wtemp = wr )*wpr - wi*wpi + wr; 
               wi = wi*wpr + wtemp*wpi + wi; 
            }
            cc = fwrite ( &afa[1], sizeof ( sReal ), KBF, file[nc] ); 
            if ( cc != KBF ) nrc_error ( "write error in nrc_fourfs" ); 
            cc = fwrite ( &afb[1], sizeof ( sReal ), KBF, file[nd] ); 
            if ( cc != KBF ) nrc_error ( "write error in nrc_fourfs" ); 
         } while ( ++ kr < nr ); 
         if ( j12 == 1 && ks != n && ks == KBF ) {
            na = mate[na]; 
            nb = na; 
         }
         if ( nr == 0 ) break; 
      }
      nrc_fourew ( file, &na, &nb, &nc, &nd ); 
      jk >>= 1; 
      while ( jk == 1 ) {
         mm = n; 
         jk = nn[++ nv]; 
      }
      ks >>= 1; 
      if ( ks > KBF ) {
         for ( j12 = 1; j12 <= 2; j12 ++ ) {
            for ( kr = 1; kr <= ns; kr += ks/KBF ) {
               for ( k = 1; k <= ks; k += KBF ) {
                  cc = fread ( &afa[1], sizeof ( sReal ), KBF, file[na] ); 
                  if ( cc != KBF ) nrc_error ( "read error in nrc_fourfs" ); 
                  cc = fwrite ( &afa[1], sizeof ( sReal ), KBF, file[nc] ); 
                  if ( cc != KBF ) nrc_error ( "write error in nrc_fourfs" ); 
               }
               nc = mate[nc]; 
            }
            na = mate[na]; 
         }
         nrc_fourew ( file, &na, &nb, &nc, &nd ); 
      } else if ( ks == KBF ) nb = na; 
      else break; 
   }
   j = 1; 
   for ( ; ; ) {
      theta = isign*3.141592653589793238462643383279502884197/( n/mm ); 
      wtemp = sin ( 0.5*theta ); 
      wpr = - 2.0*wtemp*wtemp; 
      wpi = sin ( theta ); 
      wr = 1.0; 
      wi = 0.0; 
      mm >>= 1; 
      ks = kd; 
      kd >>= 1; 
      for ( j12 = 1; j12 <= 2; j12 ++ ) {
         for ( kr = 1; kr <= ns; kr ++ ) {
            cc = fread ( &afc[1], sizeof ( sReal ), KBF, file[na] ); 
            if ( cc != KBF ) nrc_error ( "read error in nrc_fourfs" ); 
            kk = 1; 
            k = ks + 1; 
            for ( ; ; ) {
               tempr =( ( sReal ) wr )*afc[kk + ks]-( ( sReal ) wi )*afc[kk + ks + 1]; 
               tempi =( ( sReal ) wi )*afc[kk + ks]+( ( sReal ) wr )*afc[kk + ks + 1]; 
               afa[j]= afc[kk]+ tempr; 
               afb[j]= afc[kk]- tempr; 
               afa[++ j]= afc[++ kk]+ tempi; 
               afb[j ++]= afc[kk ++]- tempi; 
               if ( kk < k ) continue; 
               kc += kd; 
               if ( kc == mm ) {
                  kc = 0; 
                  wr =( wtemp = wr )*wpr - wi*wpi + wr; 
                  wi = wi*wpr + wtemp*wpi + wi; 
               }
               kk += ks; 
               if ( kk > KBF ) break; 
               else k = kk + ks; 
            }
            if ( j > KBF ) {
               cc = fwrite ( &afa[1], sizeof ( sReal ), KBF, file[nc] ); 
               if ( cc != KBF ) nrc_error ( "write error in nrc_fourfs" ); 
               cc = fwrite ( &afb[1], sizeof ( sReal ), KBF, file[nd] ); 
               if ( cc != KBF ) nrc_error ( "write error in nrc_fourfs" ); 
               j = 1; 
            }
         }
         na = mate[na]; 
      }
      nrc_fourew ( file, &na, &nb, &nc, &nd ); 
      jk >>= 1; 
      if ( jk > 1 ) continue; 
      mm = n; 
      do {
         if ( nv < ndim ) jk = nn[++ nv]; 
         else {
            nrc_free_vector ( afc, 1, KBF ); 
            nrc_free_vector ( afb, 1, KBF ); 
            nrc_free_vector ( afa, 1, KBF ); 
            return; 
         }
      } while ( jk == 1 ); 
   }
}
#undef KBF
#undef NRANSI
