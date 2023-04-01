
#define _NRC_TYPES_


/*
   Choose the precision of real numbers as you wish.
   This setting:
*/

/*
#define NR_CONST_EPSI   1.192093E-0007
#define NR_CONST_TINY   1.175494E-0038
#define NR_CONST_HUGE   3.402823E+0038
#define NR_CONST_EMIN   -1021
#define NR_CONST_EMAX   1024

#define NR_CONST_FPMIN  NR_CONST_TINY / NR_CONST_EPSI
#define NR_CONST_BIG    NR_CONST_HUGE * NR_CONST_EPSI

   typedef  float          sReal ;
   typedef  double         dReal ;
   typedef  long double    qReal ;
*/

/*
   Or this setting:
*/

#define NR_CONST_EPSI   2.2204460492503E-0016
#define NR_CONST_TINY   2.2250738585072E-0308
#define NR_CONST_HUGE   1.7976931348623E+0308
#define NR_CONST_EMIN   -1021
#define NR_CONST_EMAX   1024

#define NR_CONST_FPMIN  NR_CONST_TINY / NR_CONST_EPSI
#define NR_CONST_BIG    NR_CONST_HUGE * NR_CONST_EPSI

   typedef  double         sReal ;
   typedef  long double    dReal ;
   typedef  long double    qReal ;



   typedef  int            sInt  ;
   typedef  long           dInt  ;


#ifndef _NRC_TYPES_COMPLEX_
#define _NRC_TYPES_COMPLEX_

   typedef  struct FCOMPLEX 
   { 
      sReal r, i; 
   } sComp ; 

   typedef  struct DCOMPLEX 
   { 
      dReal r, i; 
   } dComp ; 

   typedef  struct QCOMPLEX 
   { 
      qReal r, i; 
   } qComp ; 

#endif
