
#ifndef _NRC_TYPES_
#define _NRC_TYPES_
#include "nrc_types.h"
#endif




#ifndef _ARITHCODE_DECLARE_T_
typedef struct {
	unsigned long *ilob, *iupb, *ncumfq, jdif, nc, minint, nch, ncum, nrad; 
} arithcode; 
#define _ARITHCODE_DECLARE_T_
#endif /* _ARITHCODE_DECLARE_T_ */

#ifndef _HUFFCODE_DECLARE_T_
typedef struct {
	unsigned long *icod, *ncod, *left, *right, nch, nodemax; 
} huffcode; 
#define _HUFFCODE_DECLARE_T_
#endif /* _HUFFCODE_DECLARE_T_ */

#include <stdio.h>


void nrc_addint ( dReal **uf,  dReal **uc,  dReal **res,  int nf ); 
void nrc_airy ( sReal x,  sReal *ai,  sReal *bi,  sReal *aip,  sReal *bip ); 
void nrc_amebsa ( sReal **p,  sReal y[],  int ndim,  sReal pb[], 	sReal *yb, 
	sReal ftol,  sReal ( *funk )( sReal [] ),  int *iter,  sReal temptr ); 
void nrc_amoeba ( sReal **p,  sReal y[],  int ndim,  sReal ftol, 
	sReal ( *funk )( sReal [] ),  int *iter ); 
sReal nrc_amotry ( sReal **p,  sReal y[],  sReal psum[],  int ndim, 
	sReal ( *funk )( sReal [] ),  int ihi,  sReal fac ); 
sReal nrc_amotsa ( sReal **p,  sReal y[],  sReal psum[],  int ndim,  sReal pb[], 
	sReal *yb,  sReal ( *funk )( sReal [] ),  int ihi,  sReal *yhi,  sReal fac ); 
void nrc_anneal ( sReal x[],  sReal y[],  int iorder[],  int ncity ); 
dReal nrc_anorm2 ( dReal **a,  int n ); 
void nrc_arcmak ( unsigned long nfreq[],  unsigned long nchh,  unsigned long nradd, 
	arithcode *acode ); 
void nrc_arcode ( unsigned long *ich,  unsigned char **codep,  unsigned long *lcode, 
	unsigned long *lcd,  int isign,  arithcode *acode ); 
void nrc_arcsum ( unsigned long iin[],  unsigned long iout[],  unsigned long ja, 
	int nwk,  unsigned long nrad,  unsigned long nc ); 
void nrc_asolve ( unsigned long n,  dReal b[],  dReal x[],  int itrnsp ); 
void nrc_atimes ( unsigned long n,  dReal x[],  dReal r[],  int itrnsp ); 
void nrc_avevar ( sReal data[],  unsigned long n,  sReal *ave,  sReal *var ); 
void nrc_balanc ( sReal **a,  int n ); 
void nrc_banbks ( sReal **a,  unsigned long n,  int m1,  int m2,  sReal **al, 
	unsigned long indx[],  sReal b[] ); 
void nrc_bandec ( sReal **a,  unsigned long n,  int m1,  int m2,  sReal **al, 
	unsigned long indx[],  sReal *d ); 
void nrc_banmul ( sReal **a,  unsigned long n,  int m1,  int m2,  sReal x[],  sReal b[] ); 
void nrc_bcucof ( sReal y[],  sReal y1[],  sReal y2[],  sReal y12[],  sReal d1, 
	sReal d2,  sReal **c ); 
void nrc_bcuint ( sReal y[],  sReal y1[],  sReal y2[],  sReal y12[], 
	sReal x1l,  sReal x1u,  sReal x2l,  sReal x2u,  sReal x1, 
	sReal x2,  sReal *ansy,  sReal *ansy1,  sReal *ansy2 ); 
void nrc_beschb ( dReal x,  dReal *gam1,  dReal *gam2,  dReal *gampl, 
	dReal *gammi ); 
sReal nrc_bessi ( int n,  sReal x ); 
sReal nrc_bessi0 ( sReal x ); 
sReal nrc_bessi1 ( sReal x ); 
void nrc_bessik ( sReal x,  sReal xnu,  sReal *ri,  sReal *rk,  sReal *rip, 
	sReal *rkp ); 
sReal nrc_bessj ( int n,  sReal x ); 
sReal nrc_bessj0 ( sReal x ); 
sReal nrc_bessj1 ( sReal x ); 
void nrc_bessjy ( sReal x,  sReal xnu,  sReal *nrc_rj,  sReal *ry,  sReal *rjp, 
	sReal *ryp ); 
sReal nrc_bessk ( int n,  sReal x ); 
sReal nrc_bessk0 ( sReal x ); 
sReal nrc_bessk1 ( sReal x ); 
sReal nrc_bessy ( int n,  sReal x ); 
sReal nrc_bessy0 ( sReal x ); 
sReal nrc_bessy1 ( sReal x ); 
sReal nrc_beta ( sReal z,  sReal w ); 
sReal nrc_betacf ( sReal a,  sReal b,  sReal x ); 
sReal nrc_betai ( sReal a,  sReal b,  sReal x ); 
sReal nrc_bico ( int n,  int k ); 
void nrc_bksub ( int ne,  int nb,  int jf,  int k1,  int k2,  sReal ***c ); 
sReal nrc_bnldev ( sReal pp,  int n,  long *idum ); 
sReal nrc_brent ( sReal ax,  sReal bx,  sReal cx, 
	sReal ( *f )( sReal ),  sReal tol,  sReal *xmin ); 
void nrc_broydn ( sReal x[],  int n,  int *check, 
	void ( *vecfunc )( int,  sReal [],  sReal [] ) ); 
void nrc_bsstep ( sReal y[],  sReal dydx[],  int nv,  sReal *xx,  sReal htry, 
	sReal eps,  sReal yscal[],  sReal *hdid,  sReal *hnext, 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_caldat ( long julian,  int *mm,  int *id,  int *iyyy ); 
void nrc_chder ( sReal a,  sReal b,  sReal c[],  sReal cder[],  int n ); 
sReal nrc_chebev ( sReal a,  sReal b,  sReal c[],  int m,  sReal x ); 
void nrc_chebft ( sReal a,  sReal b,  sReal c[],  int n,  sReal ( *func )( sReal ) ); 
void nrc_chebpc ( sReal c[],  sReal d[],  int n ); 
void nrc_chint ( sReal a,  sReal b,  sReal c[],  sReal cint[],  int n ); 
sReal nrc_chixy ( sReal bang ); 
void nrc_choldc ( sReal **a,  int n,  sReal p[] ); 
void nrc_cholsl ( sReal **a,  int n,  sReal p[],  sReal b[],  sReal x[] ); 
void nrc_chsone ( sReal bins[],  sReal ebins[],  int nbins,  int knstrn, 
	sReal *df,  sReal *chsq,  sReal *prob ); 
void nrc_chstwo ( sReal bins1[],  sReal bins2[],  int nbins,  int knstrn, 
	sReal *df,  sReal *chsq,  sReal *prob ); 
void nrc_cisi ( sReal x,  sReal *ci,  sReal *si ); 
void nrc_cntab1 ( int **nn,  int ni,  int nj,  sReal *chisq, 
	sReal *df,  sReal *prob,  sReal *cramrv,  sReal *ccc ); 
void nrc_cntab2 ( int **nn,  int ni,  int nj,  sReal *h,  sReal *hx,  sReal *hy, 
	sReal *hygx,  sReal *hxgy,  sReal *uygx,  sReal *uxgy,  sReal *uxy ); 
void nrc_convlv ( sReal data[],  unsigned long n,  sReal respns[],  unsigned long m, 
	int isign,  sReal ans[] ); 
void nrc_copy ( dReal **aout,  dReal **ain,  int n ); 
void nrc_correl ( sReal data1[],  sReal data2[],  unsigned long n,  sReal ans[] ); 
void nrc_cosft ( sReal y[],  int n,  int isign ); 
void nrc_cosft1 ( sReal y[],  int n ); 
void nrc_cosft2 ( sReal y[],  int n,  int isign ); 
void nrc_covsrt ( sReal **covar,  int ma,  int ia[],  int mfit ); 
void nrc_crank ( unsigned long n,  sReal w[],  sReal *s ); 
void nrc_cyclic ( sReal a[],  sReal b[],  sReal c[],  sReal alpha,  sReal nrc_beta, 
	sReal r[],  sReal x[],  unsigned long n ); 
void nrc_daub4 ( sReal a[],  unsigned long n,  int isign ); 
sReal nrc_dawson ( sReal x ); 
sReal nrc_dbrent ( sReal ax,  sReal bx,  sReal cx, 
	sReal ( *f )( sReal ),  sReal ( *df )( sReal ),  sReal tol,  sReal *xmin ); 
void nrc_ddpoly ( sReal c[],  int nc,  sReal x,  sReal pd[],  int nd ); 
int nrc_decchk ( char string[],  int n,  char *ch ); 
void nrc_derivs ( sReal x,  sReal y[],  sReal dydx[] ); 
sReal nrc_df1dim ( sReal x ); 
void nrc_dfour1 ( dReal data[],  unsigned long nn,  int isign ); 
void nrc_dfpmin ( sReal p[],  int n,  sReal gtol,  int *iter,  sReal *fret, 
	sReal ( *func )( sReal [] ),  void ( *dfunc )( sReal [],  sReal [] ) ); 
sReal nrc_dfridr ( sReal ( *func )( sReal ),  sReal x,  sReal h,  sReal *err ); 
void nrc_dftcor ( sReal w,  sReal delta,  sReal a,  sReal b,  sReal endpts[], 
	sReal *corre,  sReal *corim,  sReal *corfac ); 
void nrc_dftint ( sReal ( *func )( sReal ),  sReal a,  sReal b,  sReal w, 
	sReal *cosint,  sReal *sinint ); 
void nrc_difeq ( int k,  int k1,  int k2,  int jsf,  int is1,  int isf, 
	int indexv[],  int ne,  sReal **s,  sReal **y ); 
void nrc_dlinmin ( sReal p[],  sReal xi[],  int n,  sReal *fret, 
	sReal ( *func )( sReal [] ),  void ( *dfunc )( sReal [],  sReal[] ) ); 
dReal nrc_dpythag ( dReal a,  dReal b ); 
void nrc_drealft ( dReal data[],  unsigned long n,  int isign ); 
void nrc_dsprsax ( dReal sa[],  unsigned long ija[],  dReal x[],  dReal b[], 
	unsigned long n ); 
void nrc_dsprstx ( dReal sa[],  unsigned long ija[],  dReal x[],  dReal b[], 
	unsigned long n ); 
void nrc_dsvbksb ( dReal **u,  dReal w[],  dReal **v,  int m,  int n,  dReal b[], 
	dReal x[] ); 
void nrc_dsvdcmp ( dReal **a,  int m,  int n,  dReal w[],  dReal **v ); 
void nrc_eclass ( int nf[],  int n,  int lista[],  int listb[],  int m ); 
void nrc_eclazz ( int nf[],  int n,  int ( *equiv )( int,  int ) ); 
sReal nrc_ei ( sReal x ); 
void nrc_eigsrt ( sReal d[],  sReal **v,  int n ); 
sReal nrc_elle ( sReal phi,  sReal ak ); 
sReal nrc_ellf ( sReal phi,  sReal ak ); 
sReal nrc_ellpi ( sReal phi,  sReal en,  sReal ak ); 
void nrc_elmhes ( sReal **a,  int n ); 
sReal nrc_erfcc ( sReal x ); 
sReal nrc_erff ( sReal x ); 
sReal nrc_erffc ( sReal x ); 
void nrc_eulsum ( sReal *sum,  sReal term,  int jterm,  sReal wksp[] ); 
sReal nrc_evlmem ( sReal fdt,  sReal d[],  int m,  sReal xms ); 
sReal nrc_expdev ( long *idum ); 
sReal nrc_expint ( int n,  sReal x ); 
sReal nrc_f1 ( sReal x ); 
sReal nrc_f1dim ( sReal x ); 
sReal nrc_f2 ( sReal y ); 
sReal nrc_f3 ( sReal z ); 
sReal nrc_factln ( int n ); 
sReal nrc_factrl ( int n ); 
void nrc_fasper ( sReal x[],  sReal y[],  unsigned long n,  sReal ofac,  sReal hifac, 
	sReal wk1[],  sReal wk2[],  unsigned long nwk,  unsigned long *nout, 
	unsigned long *jmax,  sReal *prob ); 
void nrc_fdjac ( int n,  sReal x[],  sReal fvec[],  sReal **df, 
	void ( *vecfunc )( int,  sReal [],  sReal [] ) ); 
void nrc_fgauss ( sReal x,  sReal a[],  sReal *y,  sReal dyda[],  int na ); 
void nrc_fill0 ( dReal **u,  int n ); 
void nrc_fit ( sReal x[],  sReal y[],  int ndata,  sReal sig[],  int mwt, 
	sReal *a,  sReal *b,  sReal *siga,  sReal *sigb,  sReal *chi2,  sReal *q ); 
void nrc_fitexy ( sReal x[],  sReal y[],  int ndat,  sReal sigx[],  sReal sigy[], 
	sReal *a,  sReal *b,  sReal *siga,  sReal *sigb,  sReal *chi2,  sReal *q ); 
void nrc_fixrts ( sReal d[],  int m ); 
void nrc_fleg ( sReal x,  sReal pl[],  int nl ); 
void nrc_flmoon ( int n,  int nph,  long *jd,  sReal *frac ); 
sReal nrc_fmin ( sReal x[] ); 
void nrc_four1 ( sReal data[],  unsigned long nn,  int isign ); 
void nrc_fourew ( FILE *file[5],  int *na,  int *nb,  int *nc,  int *nd ); 
void nrc_fourfs ( FILE *file[5],  unsigned long nn[],  int ndim,  int isign ); 
void nrc_fourn ( sReal data[],  unsigned long nn[],  int ndim,  int isign ); 
void nrc_fpoly ( sReal x,  sReal p[],  int np ); 
void nrc_fred2 ( int n,  sReal a,  sReal b,  sReal t[],  sReal f[],  sReal w[], 
	sReal ( *g )( sReal ),  sReal ( *ak )( sReal,  sReal ) ); 
sReal nrc_fredin ( sReal x,  int n,  sReal a,  sReal b,  sReal t[],  sReal f[],  sReal w[], 
	sReal ( *g )( sReal ),  sReal ( *ak )( sReal,  sReal ) ); 
void nrc_frenel ( sReal x,  sReal *s,  sReal *c ); 
void nrc_frprmn ( sReal p[],  int n,  sReal ftol,  int *iter,  sReal *fret, 
	sReal ( *func )( sReal [] ),  void ( *dfunc )( sReal [],  sReal [] ) ); 
void nrc_ftest ( sReal data1[],  unsigned long n1,  sReal data2[],  unsigned long n2, 
	sReal *f,  sReal *prob ); 
sReal nrc_gamdev ( int ia,  long *idum ); 
sReal nrc_gammln ( sReal xx ); 
sReal nrc_gammp ( sReal a,  sReal x ); 
sReal nrc_gammq ( sReal a,  sReal x ); 
sReal nrc_gasdev ( long *idum ); 
void nrc_gaucof ( int n,  sReal a[],  sReal b[],  sReal amu0,  sReal x[],  sReal w[] ); 
void nrc_gauher ( sReal x[],  sReal w[],  int n ); 
void nrc_gaujac ( sReal x[],  sReal w[],  int n,  sReal alf,  sReal bet ); 
void nrc_gaulag ( sReal x[],  sReal w[],  int n,  sReal alf ); 
void nrc_gauleg ( sReal x1,  sReal x2,  sReal x[],  sReal w[],  int n ); 
void nrc_gaussj ( sReal **a,  int n,  sReal **b,  int m ); 
void nrc_gcf ( sReal *gammcf,  sReal a,  sReal x,  sReal *gln ); 
sReal nrc_golden ( sReal ax,  sReal bx,  sReal cx,  sReal ( *f )( sReal ),  sReal tol, 
	sReal *xmin ); 
void nrc_gser ( sReal *gamser,  sReal a,  sReal x,  sReal *gln ); 
void nrc_hpsel ( unsigned long m,  unsigned long n,  sReal arr[],  sReal heap[] ); 
void nrc_hpsort ( unsigned long n,  sReal ra[] ); 
void nrc_hqr ( sReal **a,  int n,  sReal wr[],  sReal wi[] ); 
void nrc_hufapp ( unsigned long index[],  unsigned long nprob[],  unsigned long n, 
	unsigned long i ); 
void nrc_hufdec ( unsigned long *ich,  unsigned char *code,  unsigned long lcode, 
	unsigned long *nb,  huffcode *hcode ); 
void nrc_hufenc ( unsigned long ich,  unsigned char **codep,  unsigned long *lcode, 
	unsigned long *nb,  huffcode *hcode ); 
void nrc_hufmak ( unsigned long nfreq[],  unsigned long nchin,  unsigned long *ilong, 
	unsigned long *nlong,  huffcode *hcode ); 
void nrc_hunt ( sReal xx[],  unsigned long n,  sReal x,  unsigned long *jlo ); 
void nrc_hypdrv ( sReal s,  sReal yy[],  sReal dyyds[] ); 
sComp nrc_hypgeo ( sComp a,  sComp b,  sComp c,  sComp z ); 
void nrc_hypser ( sComp a,  sComp b,  sComp c,  sComp z, 
	sComp *series,  sComp *deriv ); 
unsigned short nrc_icrc ( unsigned short crc,  unsigned char *bufptr, 
	unsigned long len,  short jinit,  int jrev ); 
unsigned short nrc_icrc1 ( unsigned short crc,  unsigned char onech ); 
unsigned long nrc_igray ( unsigned long n,  int is ); 
void nrc_iindexx ( unsigned long n,  long arr[],  unsigned long indx[] ); 
void nrc_indexx ( unsigned long n,  sReal arr[],  unsigned long indx[] ); 
void nrc_interp ( dReal **uf,  dReal **uc,  int nf ); 
int nrc_irbit1 ( unsigned long *iseed ); 
int nrc_irbit2 ( unsigned long *iseed ); 
void nrc_jacobi ( sReal **a,  int n,  sReal d[],  sReal **v,  int *nrot ); 
void nrc_jacobn ( sReal x,  sReal y[],  sReal dfdx[],  sReal **dfdy,  int n ); 
long nrc_julday ( int mm,  int id,  int iyyy ); 
void nrc_kendl1 ( sReal data1[],  sReal data2[],  unsigned long n,  sReal *tau,  sReal *z, 
	sReal *prob ); 
void nrc_kendl2 ( sReal **tab,  int i,  int j,  sReal *tau,  sReal *z,  sReal *prob ); 
void nrc_kermom ( dReal w[],  dReal y,  int m ); 
void nrc_ks2d1s ( sReal x1[],  sReal y1[],  unsigned long n1, 
	void ( *nrc_quadvl )( sReal,  sReal,  sReal *,  sReal *,  sReal *,  sReal * ), 
	sReal *d1,  sReal *prob ); 
void nrc_ks2d2s ( sReal x1[],  sReal y1[],  unsigned long n1,  sReal x2[],  sReal y2[], 
	unsigned long n2,  sReal *d,  sReal *prob ); 
void nrc_ksone ( sReal data[],  unsigned long n,  sReal ( *func )( sReal ),  sReal *d, 
	sReal *prob ); 
void nrc_kstwo ( sReal data1[],  unsigned long n1,  sReal data2[],  unsigned long n2, 
	sReal *d,  sReal *prob ); 
void nrc_laguer ( sComp a[],  int m,  sComp *x,  int *its ); 
void nrc_lfit ( sReal x[],  sReal y[],  sReal sig[],  int ndat,  sReal a[],  int ia[], 
	int ma,  sReal **covar,  sReal *chisq,  void ( *funcs )( sReal,  sReal [],  int ) ); 
void nrc_linbcg ( unsigned long n,  dReal b[],  dReal x[],  int itol,  dReal tol, 
	 int itmax,  int *iter,  dReal *err ); 
void nrc_linmin ( sReal p[],  sReal xi[],  int n,  sReal *fret, 
	sReal ( *func )( sReal [] ) ); 
void nrc_lnsrch ( int n,  sReal xold[],  sReal fold,  sReal g[],  sReal p[],  sReal x[], 
	 sReal *f,  sReal stpmax,  int *check,  sReal ( *func )( sReal [] ) ); 
void nrc_load ( sReal x1,  sReal v[],  sReal y[] ); 
void nrc_load1 ( sReal x1,  sReal v1[],  sReal y[] ); 
void nrc_load2 ( sReal x2,  sReal v2[],  sReal y[] ); 
void nrc_locate ( sReal xx[],  unsigned long n,  sReal x,  unsigned long *j ); 
void nrc_lop ( dReal **out,  dReal **u,  int n ); 
void nrc_lubksb ( sReal **a,  int n,  int *indx,  sReal b[] ); 
void nrc_ludcmp ( sReal **a,  int n,  int *indx,  sReal *d ); 
void nrc_machar ( int *ibeta,  int *it,  int *irnd,  int *ngrd, 
	int *machep,  int *negep,  int *iexp,  int *minexp,  int *maxexp, 
	sReal *eps,  sReal *epsneg,  sReal *xmin,  sReal *xmax ); 
void nrc_matadd ( dReal **a,  dReal **b,  dReal **c,  int n ); 
void nrc_matsub ( dReal **a,  dReal **b,  dReal **c,  int n ); 
void nrc_medfit ( sReal x[],  sReal y[],  int ndata,  sReal *a,  sReal *b,  sReal *abdev ); 
void nrc_memcof ( sReal data[],  int n,  int m,  sReal *xms,  sReal d[] ); 
int nrc_metrop ( sReal de,  sReal t ); 
void nrc_mgfas ( dReal **u,  int n,  int maxcyc ); 
void nrc_mglin ( dReal **u,  int n,  int ncycle ); 
sReal nrc_midexp ( sReal ( *funk )( sReal ),  sReal aa,  sReal bb,  int n ); 
sReal nrc_midinf ( sReal ( *funk )( sReal ),  sReal aa,  sReal bb,  int n ); 
sReal nrc_midpnt ( sReal ( *func )( sReal ),  sReal a,  sReal b,  int n ); 
sReal nrc_midsql ( sReal ( *funk )( sReal ),  sReal aa,  sReal bb,  int n ); 
sReal nrc_midsqu ( sReal ( *funk )( sReal ),  sReal aa,  sReal bb,  int n ); 
void nrc_miser ( sReal ( *func )( sReal [] ),  sReal regn[],  int ndim,  unsigned long npts, 
	sReal dith,  sReal *ave,  sReal *var ); 
void nrc_mmid ( sReal y[],  sReal dydx[],  int nvar,  sReal xs,  sReal htot, 
	int nstep,  sReal yout[],  void ( *nrc_derivs )( sReal,  sReal[],  sReal[] ) ); 
void nrc_mnbrak ( sReal *ax,  sReal *bx,  sReal *cx,  sReal *fa,  sReal *fb, 
	sReal *fc,  sReal ( *func )( sReal ) ); 
void nrc_mnewt ( int ntrial,  sReal x[],  int n,  sReal tolx,  sReal tolf ); 
void nrc_moment ( sReal data[],  int n,  sReal *ave,  sReal *adev,  sReal *sdev, 
	sReal *var,  sReal *skew,  sReal *curt ); 
void nrc_mp2dfr ( unsigned char a[],  unsigned char s[],  int n,  int *m ); 
void nrc_mpadd ( unsigned char w[],  unsigned char u[],  unsigned char v[],  int n ); 
void nrc_mpdiv ( unsigned char q[],  unsigned char r[],  unsigned char u[], 
	unsigned char v[],  int n,  int m ); 
void nrc_mpinv ( unsigned char u[],  unsigned char v[],  int n,  int m ); 
void nrc_mplsh ( unsigned char u[],  int n ); 
void nrc_mpmov ( unsigned char u[],  unsigned char v[],  int n ); 
void nrc_mpmul ( unsigned char w[],  unsigned char u[],  unsigned char v[],  int n, 
	int m ); 
void nrc_mpneg ( unsigned char u[],  int n ); 
void nrc_mppi ( int n ); 
void nrc_mprove ( sReal **a,  sReal **alud,  int n,  int indx[],  sReal b[], 
	sReal x[] ); 
void nrc_mpsad ( unsigned char w[],  unsigned char u[],  int n,  int iv ); 
void nrc_mpsdv ( unsigned char w[],  unsigned char u[],  int n,  int iv,  int *ir ); 
void nrc_mpsmu ( unsigned char w[],  unsigned char u[],  int n,  int iv ); 
void nrc_mpsqrt ( unsigned char w[],  unsigned char u[],  unsigned char v[],  int n, 
	int m ); 
void nrc_mpsub ( int *is,  unsigned char w[],  unsigned char u[],  unsigned char v[], 
	int n ); 
void nrc_mrqcof ( sReal x[],  sReal y[],  sReal sig[],  int ndata,  sReal a[], 
	int ia[],  int ma,  sReal **alpha,  sReal nrc_beta[],  sReal *chisq, 
	void ( *funcs )( sReal,  sReal [],  sReal *,  sReal [],  int ) ); 
void nrc_mrqmin ( sReal x[],  sReal y[],  sReal sig[],  int ndata,  sReal a[], 
	int ia[],  int ma,  sReal **covar,  sReal **alpha,  sReal *chisq, 
	void ( *funcs )( sReal,  sReal [],  sReal *,  sReal [],  int ),  sReal *alamda ); 
void nrc_newt ( sReal x[],  int n,  int *check, 
	void ( *vecfunc )( int,  sReal [],  sReal [] ) ); 
void nrc_odeint ( sReal ystart[],  int nvar,  sReal x1,  sReal x2, 
	sReal eps,  sReal h1,  sReal hmin,  int *nok,  int *nbad, 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ), 
	void ( *nrc_rkqs )( sReal [],  sReal [],  int,  sReal *,  sReal,  sReal, 
	sReal [],  sReal *,  sReal *,  void ( * )( sReal,  sReal [],  sReal [] ) ) ); 
void nrc_orthog ( int n,  sReal anu[],  sReal alpha[],  sReal nrc_beta[],  sReal a[], 
	sReal b[] ); 
void nrc_pade ( dReal cof[],  int n,  sReal *nrc_resid ); 
void nrc_pccheb ( sReal d[],  sReal c[],  int n ); 
void nrc_pcshft ( sReal a,  sReal b,  sReal d[],  int n ); 
void nrc_pearsn ( sReal x[],  sReal y[],  unsigned long n,  sReal *r,  sReal *prob, 
	sReal *z ); 
void nrc_period ( sReal x[],  sReal y[],  int n,  sReal ofac,  sReal hifac, 
	sReal px[],  sReal py[],  int np,  int *nout,  int *jmax,  sReal *prob ); 
void nrc_piksr2 ( int n,  sReal arr[],  sReal brr[] ); 
void nrc_piksrt ( int n,  sReal arr[] ); 
void nrc_pinvs ( int ie1,  int ie2,  int je1,  int jsf,  int jc1,  int k, 
	sReal ***c,  sReal **s ); 
sReal nrc_plgndr ( int l,  int m,  sReal x ); 
sReal nrc_poidev ( sReal xm,  long *idum ); 
void nrc_polcoe ( sReal x[],  sReal y[],  int n,  sReal cof[] ); 
void nrc_polcof ( sReal xa[],  sReal ya[],  int n,  sReal cof[] ); 
void nrc_poldiv ( sReal u[],  int n,  sReal v[],  int nv,  sReal q[],  sReal r[] ); 
void nrc_polin2 ( sReal x1a[],  sReal x2a[],  sReal **ya,  int m,  int n, 
	sReal x1,  sReal x2,  sReal *y,  sReal *dy ); 
void nrc_polint ( sReal xa[],  sReal ya[],  int n,  sReal x,  sReal *y,  sReal *dy ); 
void nrc_powell ( sReal p[],  sReal **xi,  int n,  sReal ftol,  int *iter,  sReal *fret, 
	sReal ( *func )( sReal [] ) ); 
void nrc_predic ( sReal data[],  int ndata,  sReal d[],  int m,  sReal future[],  int nfut ); 
sReal nrc_probks ( sReal alam ); 
void nrc_psdes ( unsigned long *lword,  unsigned long *irword ); 
void nrc_pwt ( sReal a[],  unsigned long n,  int isign ); 
void nrc_pwtset ( int n ); 
sReal nrc_pythag ( sReal a,  sReal b ); 
void nrc_pzextr ( int iest,  sReal xest,  sReal yest[],  sReal yz[],  sReal dy[], 
	int nv ); 
sReal nrc_qgaus ( sReal ( *func )( sReal ),  sReal a,  sReal b ); 
void nrc_qrdcmp ( sReal **a,  int n,  sReal *c,  sReal *d,  int *sing ); 
sReal nrc_qromb ( sReal ( *func )( sReal ),  sReal a,  sReal b ); 
sReal nrc_qromo ( sReal ( *func )( sReal ),  sReal a,  sReal b, 
	sReal ( *choose )( sReal ( * )( sReal ),  sReal,  sReal,  int ) ); 
void nrc_qroot ( sReal p[],  int n,  sReal *b,  sReal *c,  sReal eps ); 
void nrc_qrsolv ( sReal **a,  int n,  sReal c[],  sReal d[],  sReal b[] ); 
void nrc_qrupdt ( sReal **r,  sReal **qt,  int n,  sReal u[],  sReal v[] ); 
sReal nrc_qsimp ( sReal ( *func )( sReal ),  sReal a,  sReal b ); 
sReal nrc_qtrap ( sReal ( *func )( sReal ),  sReal a,  sReal b ); 
sReal nrc_quad3d ( sReal ( *func )( sReal,  sReal,  sReal ),  sReal x1,  sReal x2 ); 
void nrc_quadct ( sReal x,  sReal y,  sReal xx[],  sReal yy[],  unsigned long nn, 
	sReal *fa,  sReal *fb,  sReal *fc,  sReal *fd ); 
void nrc_quadmx ( sReal **a,  int n ); 
void nrc_quadvl ( sReal x,  sReal y,  sReal *fa,  sReal *fb,  sReal *fc,  sReal *fd ); 
sReal nrc_ran0 ( long *idum ); 
sReal nrc_ran1 ( long *idum ); 
sReal nrc_ran2 ( long *idum ); 
sReal nrc_ran3 ( long *idum ); 
sReal nrc_ran4 ( long *idum ); 
void nrc_rank ( unsigned long n,  unsigned long indx[],  unsigned long irank[] ); 
void nrc_ranpt ( sReal pt[],  sReal regn[],  int n ); 
void nrc_ratint ( sReal xa[],  sReal ya[],  int n,  sReal x,  sReal *y,  sReal *dy ); 
void nrc_ratlsq ( dReal ( *fn )( dReal ),  dReal a,  dReal b,  int mm,  int kk, 
	dReal cof[],  dReal *dev ); 
dReal nrc_ratval ( dReal x,  dReal cof[],  int mm,  int kk ); 
sReal nrc_rc ( sReal x,  sReal y ); 
sReal nrc_rd ( sReal x,  sReal y,  sReal z ); 
void nrc_realft ( sReal data[],  unsigned long n,  int isign ); 
void nrc_rebin ( sReal nrc_rc,  int nd,  sReal r[],  sReal xin[],  sReal xi[] ); 
void nrc_red ( int iz1,  int iz2,  int jz1,  int jz2,  int jm1,  int jm2,  int jmf, 
	int ic1,  int jc1,  int jcf,  int kc,  sReal ***c,  sReal **s ); 
void nrc_relax ( dReal **u,  dReal **rhs,  int n ); 
void nrc_relax2 ( dReal **u,  dReal **rhs,  int n ); 
void nrc_resid ( dReal **res,  dReal **u,  dReal **rhs,  int n ); 
sReal nrc_revcst ( sReal x[],  sReal y[],  int iorder[],  int ncity,  int n[] ); 
void nrc_reverse ( int iorder[],  int ncity,  int n[] ); 
sReal nrc_rf ( sReal x,  sReal y,  sReal z ); 
sReal nrc_rj ( sReal x,  sReal y,  sReal z,  sReal p ); 
void nrc_rk4 ( sReal y[],  sReal dydx[],  int n,  sReal x,  sReal h,  sReal yout[], 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_rkck ( sReal y[],  sReal dydx[],  int n,  sReal x,  sReal h, 
	sReal yout[],  sReal yerr[],  void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_rkdumb ( sReal vstart[],  int nvar,  sReal x1,  sReal x2,  int nstep, 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_rkqs ( sReal y[],  sReal dydx[],  int n,  sReal *x, 
	sReal htry,  sReal eps,  sReal yscal[],  sReal *hdid,  sReal *hnext, 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_rlft3 ( sReal ***data,  sReal **speq,  unsigned long nn1, 
	unsigned long nn2,  unsigned long nn3,  int isign ); 
sReal nrc_rofunc ( sReal b ); 
void nrc_rotate ( sReal **r,  sReal **qt,  int n,  int i,  sReal a,  sReal b ); 
void nrc_rsolv ( sReal **a,  int n,  sReal d[],  sReal b[] ); 
void nrc_rstrct ( dReal **uc,  dReal **uf,  int nc ); 
sReal nrc_rtbis ( sReal ( *func )( sReal ),  sReal x1,  sReal x2,  sReal xacc ); 
sReal nrc_rtflsp ( sReal ( *func )( sReal ),  sReal x1,  sReal x2,  sReal xacc ); 
sReal nrc_rtnewt ( void ( *funcd )( sReal,  sReal *,  sReal * ),  sReal x1,  sReal x2, 
	sReal xacc ); 
sReal nrc_rtsafe ( void ( *funcd )( sReal,  sReal *,  sReal * ),  sReal x1,  sReal x2, 
	sReal xacc ); 
sReal nrc_rtsec ( sReal ( *func )( sReal ),  sReal x1,  sReal x2,  sReal xacc ); 
void nrc_rzextr ( int iest,  sReal xest,  sReal yest[],  sReal yz[],  sReal dy[],  int nv ); 
void nrc_savgol ( sReal c[],  int np,  int nl,  int nr,  int ld,  int m ); 
void nrc_score ( sReal xf,  sReal y[],  sReal f[] ); 
void nrc_scrsho ( sReal ( *fx )( sReal ) ); 
sReal nrc_select ( unsigned long k,  unsigned long n,  sReal arr[] ); 
sReal nrc_selip ( unsigned long k,  unsigned long n,  sReal arr[] ); 
void nrc_shell ( unsigned long n,  sReal a[] ); 
void nrc_shoot ( int n,  sReal v[],  sReal f[] ); 
void nrc_shootf ( int n,  sReal v[],  sReal f[] ); 
void nrc_simp1 ( sReal **a,  int mm,  int ll[],  int nll,  int iabf,  int *kp, 
	sReal *bmax ); 
void nrc_simp2 ( sReal **a,  int m,  int n,  int *ip,  int kp ); 
void nrc_simp3 ( sReal **a,  int i1,  int k1,  int ip,  int kp ); 
void nrc_simplx ( sReal **a,  int m,  int n,  int m1,  int m2,  int m3,  int *icase, 
	int izrov[],  int iposv[] ); 
void nrc_simpr ( sReal y[],  sReal dydx[],  sReal dfdx[],  sReal **dfdy, 
	int n,  sReal xs,  sReal htot,  int nstep,  sReal yout[], 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_sinft ( sReal y[],  int n ); 
void nrc_slvsm2 ( dReal **u,  dReal **rhs ); 
void nrc_slvsml ( dReal **u,  dReal **rhs ); 
void nrc_sncndn ( sReal uu,  sReal emmc,  sReal *sn,  sReal *cn,  sReal *dn ); 
dReal nrc_snrm ( unsigned long n,  dReal sx[],  int itol ); 
void nrc_sobseq ( int *n,  sReal x[] ); 
void nrc_solvde ( int itmax,  sReal conv,  sReal slowc,  sReal scalv[], 
	int indexv[],  int ne,  int nb,  int m,  sReal **y,  sReal ***c,  sReal **s ); 
void nrc_sor ( dReal **a,  dReal **b,  dReal **c,  dReal **d,  dReal **e, 
	dReal **f,  dReal **u,  int jmax,  dReal rjac ); 
void nrc_sort ( unsigned long n,  sReal arr[] ); 
void nrc_sort2 ( unsigned long n,  sReal arr[],  sReal brr[] ); 
void nrc_sort3 ( unsigned long n,  sReal ra[],  sReal rb[],  sReal nrc_rc[] ); 
void nrc_spctrm ( FILE *fp,  sReal p[],  int m,  int k,  int ovrlap ); 
void nrc_spear ( sReal data1[],  sReal data2[],  unsigned long n,  sReal *d,  sReal *zd, 
	sReal *probd,  sReal *rs,  sReal *probrs ); 
void nrc_sphbes ( int n,  sReal x,  sReal *sj,  sReal *sy,  sReal *sjp,  sReal *syp ); 
void nrc_splie2 ( sReal x1a[],  sReal x2a[],  sReal **ya,  int m,  int n,  sReal **y2a ); 
void nrc_splin2 ( sReal x1a[],  sReal x2a[],  sReal **ya,  sReal **y2a,  int m,  int n, 
	sReal x1,  sReal x2,  sReal *y ); 
void nrc_spline ( sReal x[],  sReal y[],  int n,  sReal yp1,  sReal ypn,  sReal y2[] ); 
void nrc_splint ( sReal xa[],  sReal ya[],  sReal y2a[],  int n,  sReal x,  sReal *y ); 
void nrc_spread ( sReal y,  sReal yy[],  unsigned long n,  sReal x,  int m ); 
void nrc_sprsax ( sReal sa[],  unsigned long ija[],  sReal x[],  sReal b[], 
	unsigned long n ); 
void nrc_sprsin ( sReal **a,  int n,  sReal thresh,  unsigned long nmax,  sReal sa[], 
	unsigned long ija[] ); 
void nrc_sprspm ( sReal sa[],  unsigned long ija[],  sReal sb[],  unsigned long ijb[], 
	sReal sc[],  unsigned long ijc[] ); 
void nrc_sprstm ( sReal sa[],  unsigned long ija[],  sReal sb[],  unsigned long ijb[], 
	sReal thresh,  unsigned long nmax,  sReal sc[],  unsigned long ijc[] ); 
void nrc_sprstp ( sReal sa[],  unsigned long ija[],  sReal sb[],  unsigned long ijb[] ); 
void nrc_sprstx ( sReal sa[],  unsigned long ija[],  sReal x[],  sReal b[], 
	unsigned long n ); 
void nrc_stifbs ( sReal y[],  sReal dydx[],  int nv,  sReal *xx, 
	sReal htry,  sReal eps,  sReal yscal[],  sReal *hdid,  sReal *hnext, 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_stiff ( sReal y[],  sReal dydx[],  int n,  sReal *x, 
	sReal htry,  sReal eps,  sReal yscal[],  sReal *hdid,  sReal *hnext, 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_stoerm ( sReal y[],  sReal d2y[],  int nv,  sReal xs, 
	sReal htot,  int nstep,  sReal yout[], 
	void ( *nrc_derivs )( sReal,  sReal [],  sReal [] ) ); 
void nrc_svbksb ( sReal **u,  sReal w[],  sReal **v,  int m,  int n,  sReal b[], 
	sReal x[] ); 
void nrc_svdcmp ( sReal **a,  int m,  int n,  sReal w[],  sReal **v ); 
void nrc_svdfit ( sReal x[],  sReal y[],  sReal sig[],  int ndata,  sReal a[], 
	int ma,  sReal **u,  sReal **v,  sReal w[],  sReal *chisq, 
	void ( *funcs )( sReal,  sReal [],  int ) ); 
void nrc_svdvar ( sReal **v,  int ma,  sReal w[],  sReal **cvm ); 
void nrc_toeplz ( sReal r[],  sReal x[],  sReal y[],  int n ); 
void nrc_tptest ( sReal data1[],  sReal data2[],  unsigned long n,  sReal *t,  sReal *prob ); 
void nrc_tqli ( sReal d[],  sReal e[],  int n,  sReal **z ); 
sReal nrc_trapzd ( sReal ( *func )( sReal ),  sReal a,  sReal b,  int n ); 
void nrc_tred2 ( sReal **a,  int n,  sReal d[],  sReal e[] ); 
void nrc_tridag ( sReal a[],  sReal b[],  sReal c[],  sReal r[],  sReal u[], 
	unsigned long n ); 
sReal nrc_trncst ( sReal x[],  sReal y[],  int iorder[],  int ncity,  int n[] ); 
void nrc_trnspt ( int iorder[],  int ncity,  int n[] ); 
void nrc_ttest ( sReal data1[],  unsigned long n1,  sReal data2[],  unsigned long n2, 
	sReal *t,  sReal *prob ); 
void nrc_tutest ( sReal data1[],  unsigned long n1,  sReal data2[],  unsigned long n2, 
	sReal *t,  sReal *prob ); 
void nrc_twofft ( sReal data1[],  sReal data2[],  sReal fft1[],  sReal fft2[], 
	unsigned long n ); 
void nrc_vander ( dReal x[],  dReal w[],  dReal q[],  int n ); 
void nrc_vegas ( sReal regn[],  int ndim,  sReal ( *fxn )( sReal [],  sReal ),  int init, 
	unsigned long ncall,  int itmx,  int nprn,  sReal *tgral,  sReal *sd, 
	sReal *chi2a ); 
void nrc_voltra ( int n,  int m,  sReal t0,  sReal h,  sReal *t,  sReal **f, 
	sReal ( *g )( int,  sReal ),  sReal ( *ak )( int,  int,  sReal,  sReal ) ); 
void nrc_wt1 ( sReal a[],  unsigned long n,  int isign, 
	void ( *wtstep )( sReal [],  unsigned long,  int ) ); 
void nrc_wtn ( sReal a[],  unsigned long nn[],  int ndim,  int isign, 
	void ( *wtstep )( sReal [],  unsigned long,  int ) ); 
void nrc_wwghts ( sReal wghts[],  int n,  sReal h, 
	void ( *nrc_kermom )( dReal [],  dReal , int ) ); 
int nrc_zbrac ( sReal ( *func )( sReal ),  sReal *x1,  sReal *x2 ); 
void nrc_zbrak ( sReal ( *fx )( sReal ),  sReal x1,  sReal x2,  int n,  sReal xb1[], 
	sReal xb2[],  int *nb ); 
sReal nrc_zbrent ( sReal ( *func )( sReal ),  sReal x1,  sReal x2,  sReal tol ); 
void nrc_zrhqr ( sReal a[],  int m,  sReal rtr[],  sReal rti[] ); 
sReal nrc_zriddr ( sReal ( *func )( sReal ),  sReal x1,  sReal x2,  sReal xacc ); 
void nrc_zroots ( sComp a[],  int m,  sComp roots[],  int polish ); 


#ifndef _NRC_UTILS_
#define _NRC_UTILS_
#include "nrc_util.h"
#endif

#ifndef _NRC_COMPLEX_
#define _NRC_COMPLEX_
#include "nrc_complex.h"
#endif




