
#define _NRC_UTILS_


#ifndef _NRC_TYPES_
#define _NRC_TYPES_
#include "nrc_types.h"
#endif



static sReal sqrarg; 
#define SQR(a) ( (sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg )

static dReal dsqrarg; 
#define DSQR(a) ( (dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg )

static dReal dmaxarg1, dmaxarg2; 
#define DMAX(a,b) ( dmaxarg1=(a), dmaxarg2=(b), (dmaxarg1) > (dmaxarg2) ?\
        (dmaxarg1) : (dmaxarg2) )

static dReal dminarg1, dminarg2; 
#define DMIN(a,b) ( dminarg1=(a), dminarg2=(b), (dminarg1) < (dminarg2) ?\
        (dminarg1) : (dminarg2) )

static sReal maxarg1, maxarg2; 
#define FMAX(a,b) ( maxarg1=(a), maxarg2=(b), (maxarg1) > (maxarg2) ?\
        (maxarg1) : (maxarg2) )

static sReal minarg1, minarg2; 
#define FMIN(a,b) ( minarg1=(a), minarg2=(b), (minarg1) < (minarg2) ?\
        (minarg1) : (minarg2) )

static long lmaxarg1, lmaxarg2; 
#define LMAX(a,b) ( lmaxarg1=(a), lmaxarg2=(b), (lmaxarg1) > (lmaxarg2) ?\
        (lmaxarg1) : (lmaxarg2) )

static long lminarg1, lminarg2; 
#define LMIN(a,b) ( lminarg1=(a), lminarg2=(b), (lminarg1) < (lminarg2) ?\
        (lminarg1) : (lminarg2) )

static int imaxarg1, imaxarg2; 
#define IMAX(a,b) ( imaxarg1=(a), imaxarg2=(b), (imaxarg1) > (imaxarg2) ?\
        (imaxarg1) : (imaxarg2) )

static int iminarg1, iminarg2; 
#define IMIN(a,b) ( iminarg1=(a), iminarg2=(b), (iminarg1) < (iminarg2) ?\
        (iminarg1) : (iminarg2) )

#define SIGN(a,b) ( (b) >= 0.0 ? fabs(a) : -fabs(a) )


void nrc_error ( char error_text[] ); 
sReal *nrc_vector ( long nl,  long nh ); 
int *nrc_ivector ( long nl,  long nh ); 
unsigned char *nrc_cvector ( long nl,  long nh ); 
unsigned long *nrc_lvector ( long nl,  long nh ); 
dReal *nrc_dvector ( long nl,  long nh ); 
sReal **nrc_matrix ( long nrl,  long nrh,  long ncl,  long nch ); 
dReal **nrc_dmatrix ( long nrl,  long nrh,  long ncl,  long nch ); 
int **nrc_imatrix ( long nrl,  long nrh,  long ncl,  long nch ); 
sReal **nrc_submatrix ( sReal **a,  long oldrl,  long oldrh,  long oldcl,  long oldch, 
	long newrl,  long newcl ); 
sReal **nrc_convert_matrix ( sReal *a,  long nrl,  long nrh,  long ncl,  long nch ); 
sReal ***nrc_f3tensor ( long nrl,  long nrh,  long ncl,  long nch,  long ndl,  long ndh ); 
void nrc_free_vector ( sReal *v,  long nl,  long nh ); 
void nrc_free_ivector ( int *v,  long nl,  long nh ); 
void nrc_free_cvector ( unsigned char *v,  long nl,  long nh ); 
void nrc_free_lvector ( unsigned long *v,  long nl,  long nh ); 
void nrc_free_dvector ( dReal *v,  long nl,  long nh ); 
void nrc_free_matrix ( sReal **m,  long nrl,  long nrh,  long ncl,  long nch ); 
void nrc_free_dmatrix ( dReal **m,  long nrl,  long nrh,  long ncl,  long nch ); 
void nrc_free_imatrix ( int **m,  long nrl,  long nrh,  long ncl,  long nch ); 
void nrc_free_submatrix ( sReal **b,  long nrl,  long nrh,  long ncl,  long nch ); 
void nrc_free_convert_matrix ( sReal **b,  long nrl,  long nrh,  long ncl,  long nch ); 
void nrc_free_f3tensor ( sReal ***t,  long nrl,  long nrh,  long ncl,  long nch, 
	long ndl,  long ndh ); 

