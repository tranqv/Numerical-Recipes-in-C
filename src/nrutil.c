
#include "nrc_types.h"
/* CAUTION: This is the ANSI C ( only ) version of the Numerical Recipes
   utility file nrutil.c.  Do not confuse this file with the same - named
   file nrutil.c that is supplied in the same subdirectory or archive
   as the header file nrc_util.h.  *That* file contains both ANSI and
   traditional K&R versions, along with #ifdef macros to nrc_select the
   correct version.  *This* file contains only ANSI C.               */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define NR_END 1
#define FREE_ARG char*

void nrc_error ( char error_text[] )
/* Numerical Recipes standard error handler */
{
   fprintf ( stderr, "Numerical Recipes run - time error...\n" ); 
   fprintf ( stderr, "%s\n", error_text ); 
   fprintf ( stderr, "...now exiting to system...\n" ); 
   exit ( 1 ); 
}

sReal *nrc_vector ( long nl, long nh )
/* allocate a sReal nrc_vector with subscript range v[nl..nh] */
{
   sReal *v; 

   v =( sReal * ) malloc ( ( size_t ) ( ( nh - nl + 1 + NR_END )*sizeof ( sReal ) ) ); 
   if ( !v ) nrc_error ( "allocation failure in nrc_vector ( )" ); 
   return v - nl + NR_END; 
}

int *nrc_ivector ( long nl, long nh )
/* allocate an int nrc_vector with subscript range v[nl..nh] */
{
   int *v; 

   v =( int * ) malloc ( ( size_t ) ( ( nh - nl + 1 + NR_END )*sizeof ( int ) ) ); 
   if ( !v ) nrc_error ( "allocation failure in nrc_ivector ( )" ); 
   return v - nl + NR_END; 
}

unsigned char *nrc_cvector ( long nl, long nh )
/* allocate an unsigned char nrc_vector with subscript range v[nl..nh] */
{
   unsigned char *v; 

   v =( unsigned char * ) malloc ( ( size_t ) ( ( nh - nl + 1 + NR_END )*sizeof ( unsigned char ) ) ); 
   if ( !v ) nrc_error ( "allocation failure in nrc_cvector ( )" ); 
   return v - nl + NR_END; 
}

unsigned long *nrc_lvector ( long nl, long nh )
/* allocate an unsigned long nrc_vector with subscript range v[nl..nh] */
{
   unsigned long *v; 

   v =( unsigned long * ) malloc ( ( size_t ) ( ( nh - nl + 1 + NR_END )*sizeof ( long ) ) ); 
   if ( !v ) nrc_error ( "allocation failure in nrc_lvector ( )" ); 
   return v - nl + NR_END; 
}

dReal *nrc_dvector ( long nl, long nh )
/* allocate a dReal nrc_vector with subscript range v[nl..nh] */
{
   dReal *v; 

   v =( dReal * ) malloc ( ( size_t ) ( ( nh - nl + 1 + NR_END )*sizeof ( dReal ) ) ); 
   if ( !v ) nrc_error ( "allocation failure in nrc_dvector ( )" ); 
   return v - nl + NR_END; 
}

sReal **nrc_matrix ( long nrl, long nrh, long ncl, long nch )
/* allocate a sReal nrc_matrix with subscript range m[nrl..nrh][ncl..nch] */
{
   long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1; 
   sReal **m; 

   /* allocate pointers to rows */
   m =( sReal ** ) malloc ( ( size_t )( ( nrow + NR_END )*sizeof ( sReal* ) ) ); 
   if ( !m ) nrc_error ( "allocation failure 1 in nrc_matrix ( )" ); 
   m += NR_END; 
   m -= nrl; 

   /* allocate rows and set pointers to them */
   m[nrl]=( sReal * ) malloc ( ( size_t )( ( nrow*ncol + NR_END )*sizeof ( sReal ) ) ); 
   if ( !m[nrl] ) nrc_error ( "allocation failure 2 in nrc_matrix ( )" ); 
   m[nrl] += NR_END; 
   m[nrl] -= ncl; 

   for ( i = nrl + 1; i <= nrh; i ++ ) m[i]= m[i - 1]+ ncol; 

   /* return pointer to array of pointers to rows */
   return m; 
}

dReal **nrc_dmatrix ( long nrl, long nrh, long ncl, long nch )
/* allocate a dReal nrc_matrix with subscript range m[nrl..nrh][ncl..nch] */
{
   long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1; 
   dReal **m; 

   /* allocate pointers to rows */
   m =( dReal ** ) malloc ( ( size_t )( ( nrow + NR_END )*sizeof ( dReal* ) ) ); 
   if ( !m ) nrc_error ( "allocation failure 1 in nrc_matrix ( )" ); 
   m += NR_END; 
   m -= nrl; 

   /* allocate rows and set pointers to them */
   m[nrl]=( dReal * ) malloc ( ( size_t )( ( nrow*ncol + NR_END )*sizeof ( dReal ) ) ); 
   if ( !m[nrl] ) nrc_error ( "allocation failure 2 in nrc_matrix ( )" ); 
   m[nrl] += NR_END; 
   m[nrl] -= ncl; 

   for ( i = nrl + 1; i <= nrh; i ++ ) m[i]= m[i - 1]+ ncol; 

   /* return pointer to array of pointers to rows */
   return m; 
}

int **nrc_imatrix ( long nrl, long nrh, long ncl, long nch )
/* allocate a int nrc_matrix with subscript range m[nrl..nrh][ncl..nch] */
{
   long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1; 
   int **m; 

   /* allocate pointers to rows */
   m =( int ** ) malloc ( ( size_t )( ( nrow + NR_END )*sizeof ( int* ) ) ); 
   if ( !m ) nrc_error ( "allocation failure 1 in nrc_matrix ( )" ); 
   m += NR_END; 
   m -= nrl; 


   /* allocate rows and set pointers to them */
   m[nrl]=( int * ) malloc ( ( size_t )( ( nrow*ncol + NR_END )*sizeof ( int ) ) ); 
   if ( !m[nrl] ) nrc_error ( "allocation failure 2 in nrc_matrix ( )" ); 
   m[nrl] += NR_END; 
   m[nrl] -= ncl; 

   for ( i = nrl + 1; i <= nrh; i ++ ) m[i]= m[i - 1]+ ncol; 

   /* return pointer to array of pointers to rows */
   return m; 
}

sReal **nrc_submatrix ( sReal **a, long oldrl, long oldrh, long oldcl, long oldch, 
   long newrl, long newcl )
/* point a nrc_submatrix [newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch] */
{
   long i, j, nrow = oldrh - oldrl + 1, ncol = oldcl - newcl; 
   sReal **m; 

   /* allocate array of pointers to rows */
   m =( sReal ** ) malloc ( ( size_t ) ( ( nrow + NR_END )*sizeof ( sReal* ) ) ); 
   if ( !m ) nrc_error ( "allocation failure in nrc_submatrix ( )" ); 
   m += NR_END; 
   m -= newrl; 

   /* set pointers to rows */
   for ( i = oldrl, j = newrl; i <= oldrh; i ++, j ++ ) m[j]= a[i]+ ncol; 

   /* return pointer to array of pointers to rows */
   return m; 
}

sReal **nrc_convert_matrix ( sReal *a, long nrl, long nrh, long ncl, long nch )
/* allocate a sReal nrc_matrix m[nrl..nrh][ncl..nch] that points to the nrc_matrix
declared in the standard C manner as a[nrow][ncol], where nrow = nrh - nrl + 1
and ncol = nch - ncl + 1. The routine should be called with the address
&a[0][0] as the first argument. */
{
   long i, j, nrow = nrh - nrl + 1, ncol = nch - ncl + 1; 
   sReal **m; 

   /* allocate pointers to rows */
   m =( sReal ** ) malloc ( ( size_t ) ( ( nrow + NR_END )*sizeof ( sReal* ) ) ); 
   if ( !m ) nrc_error ( "allocation failure in nrc_convert_matrix ( )" ); 
   m += NR_END; 
   m -= nrl; 

   /* set pointers to rows */
   m[nrl]= a - ncl; 
   for ( i = 1, j = nrl + 1; i < nrow; i ++, j ++ ) m[j]= m[j - 1]+ ncol; 
   /* return pointer to array of pointers to rows */
   return m; 
}

sReal ***nrc_f3tensor ( long nrl, long nrh, long ncl, long nch, long ndl, long ndh )
/* allocate a sReal 3tensor with range t[nrl..nrh][ncl..nch][ndl..ndh] */
{
   long i, j, nrow = nrh - nrl + 1, ncol = nch - ncl + 1, ndep = ndh - ndl + 1; 
   sReal ***t; 

   /* allocate pointers to pointers to rows */
   t =( sReal *** ) malloc ( ( size_t )( ( nrow + NR_END )*sizeof ( sReal** ) ) ); 
   if ( !t ) nrc_error ( "allocation failure 1 in nrc_f3tensor ( )" ); 
   t += NR_END; 
   t -= nrl; 

   /* allocate pointers to rows and set pointers to them */
   t[nrl]=( sReal ** ) malloc ( ( size_t )( ( nrow*ncol + NR_END )*sizeof ( sReal* ) ) ); 
   if ( !t[nrl] ) nrc_error ( "allocation failure 2 in nrc_f3tensor ( )" ); 
   t[nrl] += NR_END; 
   t[nrl] -= ncl; 

   /* allocate rows and set pointers to them */
   t[nrl][ncl]=( sReal * ) malloc ( ( size_t )( ( nrow*ncol*ndep + NR_END )*sizeof ( sReal ) ) ); 
   if ( !t[nrl][ncl] ) nrc_error ( "allocation failure 3 in nrc_f3tensor ( )" ); 
   t[nrl][ncl] += NR_END; 
   t[nrl][ncl] -= ndl; 

   for ( j = ncl + 1; j <= nch; j ++ ) t[nrl][j]= t[nrl][j - 1]+ ndep; 
   for ( i = nrl + 1; i <= nrh; i ++ ) {
      t[i]= t[i - 1]+ ncol; 
      t[i][ncl]= t[i - 1][ncl]+ ncol*ndep; 
      for ( j = ncl + 1; j <= nch; j ++ ) t[i][j]= t[i][j - 1]+ ndep; 
   }

   /* return pointer to array of pointers to rows */
   return t; 
}

void nrc_free_vector ( sReal *v, long nl, long nh )
/* free a sReal nrc_vector allocated with nrc_vector ( ) */
{
   free ( ( FREE_ARG ) ( v + nl - NR_END ) ); 
}

void nrc_free_ivector ( int *v, long nl, long nh )
/* free an int nrc_vector allocated with nrc_ivector ( ) */
{
   free ( ( FREE_ARG ) ( v + nl - NR_END ) ); 
}

void nrc_free_cvector ( unsigned char *v, long nl, long nh )
/* free an unsigned char nrc_vector allocated with nrc_cvector ( ) */
{
   free ( ( FREE_ARG ) ( v + nl - NR_END ) ); 
}

void nrc_free_lvector ( unsigned long *v, long nl, long nh )
/* free an unsigned long nrc_vector allocated with nrc_lvector ( ) */
{
   free ( ( FREE_ARG ) ( v + nl - NR_END ) ); 
}

void nrc_free_dvector ( dReal *v, long nl, long nh )
/* free a dReal nrc_vector allocated with nrc_dvector ( ) */
{
   free ( ( FREE_ARG ) ( v + nl - NR_END ) ); 
}

void nrc_free_matrix ( sReal **m, long nrl, long nrh, long ncl, long nch )
/* free a sReal nrc_matrix allocated by nrc_matrix ( ) */
{
   free ( ( FREE_ARG ) ( m[nrl]+ ncl - NR_END ) ); 
   free ( ( FREE_ARG ) ( m + nrl - NR_END ) ); 
}

void nrc_free_dmatrix ( dReal **m, long nrl, long nrh, long ncl, long nch )
/* free a dReal nrc_matrix allocated by nrc_dmatrix ( ) */
{
   free ( ( FREE_ARG ) ( m[nrl]+ ncl - NR_END ) ); 
   free ( ( FREE_ARG ) ( m + nrl - NR_END ) ); 
}

void nrc_free_imatrix ( int **m, long nrl, long nrh, long ncl, long nch )
/* free an int nrc_matrix allocated by nrc_imatrix ( ) */
{
   free ( ( FREE_ARG ) ( m[nrl]+ ncl - NR_END ) ); 
   free ( ( FREE_ARG ) ( m + nrl - NR_END ) ); 
}

void nrc_free_submatrix ( sReal **b, long nrl, long nrh, long ncl, long nch )
/* free a nrc_submatrix allocated by nrc_submatrix ( ) */
{
   free ( ( FREE_ARG ) ( b + nrl - NR_END ) ); 
}

void nrc_free_convert_matrix ( sReal **b, long nrl, long nrh, long ncl, long nch )
/* free a nrc_matrix allocated by nrc_convert_matrix ( ) */
{
   free ( ( FREE_ARG ) ( b + nrl - NR_END ) ); 
}

void nrc_free_f3tensor ( sReal ***t, long nrl, long nrh, long ncl, long nch, 
   long ndl, long ndh )
/* free a sReal nrc_f3tensor allocated by nrc_f3tensor ( ) */
{
   free ( ( FREE_ARG ) ( t[nrl][ncl]+ ndl - NR_END ) ); 
   free ( ( FREE_ARG ) ( t[nrl]+ ncl - NR_END ) ); 
   free ( ( FREE_ARG ) ( t + nrl - NR_END ) ); 
}
