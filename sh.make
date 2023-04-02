#!/bin/bash 
#

########################################################################
#
#     How to use this script? 
#
#     Run 
#
#        ./sh.make
#
#     Or, 
#
#        bash sh.make 
#
#     Then you'll see what to do. 
#
########################################################################

   SRC="src"
   TST="test" 
   DAT="data"
   lib="libNRinC.a" 

   prefix=${HOME}/apps/shared

#
#
#

   aDIR=( $SRC $TST )
   nDIR=${#aDIR[@]}

   aSRC=( $SRC )
   nSRC=${#aSRC[@]}

   aLIB=( $lib )


#
#
   ODIR=${prefix}

   build=${ODIR}/build 

   OTMP=${build}/tmp 

   OBIN=${ODIR}/bin 
   OLIB=${ODIR}/lib
   OINC=${ODIR}/include 
   OOBJ=${ODIR}/obj 

   IINC=`pwd`/$SRC
   PDAT=`pwd`/$DAT 

   libna=$lib
   mylib=${OLIB}/${libna}

   COMP=""
   DEPS=""
   OPTI=""
   FLAG=""

#  arFLAG="r"
   arFLAG="rcs"

#
#  Delay='timeout'
#  Dtime='1s'

#
#  GNU COMPILER:
#

_use_gcc ()
{
   COMP="gcc"
#  DEPS="-std=c90"
   DEPS="-ansi"
   OPTI="-O3"
   FLAG="$OPTI $DEPS -I ./ -I $IINC "
}


#
#  INTEL COMPILER:
#  

_use_icc ()
{
#  COMP="icc"
   COMP="icc_run icc"
#  DEPS="-ansi"
   DEPS="-diag-disable=10441 -ansi"
   OPTI="-O3"
   FLAG="$OPTI $DEPS -I./ -I$IINC "
}
#
#  icc: remark #10441: The Intel(R) C++ Compiler Classic (ICC) is deprecated and will be removed from product release in the second half of 2023. The Intel(R) oneAPI DPC++/C++ Compiler (ICX) is the recommended compiler moving forward. Please transition to use this compiler. Use '-diag-disable=10441' to disable this message.
#

#
#  CHOOSE YOUR COMPILER:

#  _use_icc 
   _use_gcc 


   echo "COMP = $COMP"
   echo "DEPS = $DEPS"
   echo "OPTI = $OPTI"
## echo "FLAG = $FLAG"

   echo "arFLAG = $arFLAG"

   mkdir -p $OLIB $OINC $OBIN $OOBJ $build 

#######################################################################
#
#  subroutines:
#
#######################################################################

_print_usage ()
{
cat << XXX
      COMMAND         ARGUMENT       ROUTINE 
      $0       lib            _make_lib 
      $0       test           _make_test  
      $0       clean          _make_clean 
      $0       distclean      _make_distclean 
      $0       all            _make_clean && _make_lib && _make_test 
      $0       showme         _make_showme    
      $0       test  xr*.c    _make_main_glob  test  xr*.c  

Examples:             
      $0  all           to run everything, i.e., ./sh_make src, lib, and test.
      $0  distclean     to clean all the outputs. 
      $0  clean         to clean only .o and .exe files
      $0  lib           to make the lib: ${libna}
      $0  test          to compile, link, and run all the tests.
      $0  showme        to show flags to compile programs and link to the lib.
      $0  test  xr*.c   to compile, link, and run all test/xr*.c files.

At the first time, we can run the following commands stepwise:
      $0  clean       
      $0  lib        
      $0  test      
XXX
}
#




_make_test ()
{
   echo "########################################################################"
   echo "Go to $TST"

   here=`pwd`

   aux="$OPTI $DEPS"

   cd $TST
   ln -fs ../${DAT}/* . 

   for f in `ls *.c`
   do 
      echo '----------------------------------------------------------'
      h=`basename $f .c`
      g=${h}.exe 
      k=${h}.inp 
      set -x 
      ${COMP} ${OPTI} ${DEPS} -I${OINC}  $f  $mylib -lm -o $g 
      if [ -f $k ]
      then 
         ./$g < $k 
      else 
         ./$g
      fi 
      set +x 
   done 
#  rm  *.dat
   cd $here 
   unset here 
#
   echo "Done. Leave $TST"
   echo 
   echo "Note: Tests which need input from keyboard will be skiped"
   echo "      Run them manually later."
   echo 
   echo "########################################################################"
}
#


_make_main_glob ()
{
   dir=$1 ; shift ;
   pat=$1 ; shift ;


   echo "########################################################################"
   echo "Go to $dir"

   here=`pwd`

   aux="$OPTI $DEPS"

   cd $dir
   ln -fs ${PDAT}/* . 

   for f in `ls $pat `
   do 
      echo '----------------------------------------------------------'
      h=`basename $f .c`
      g=${h}.exe 
      k=${h}.inp 
      set -x 
      ${COMP} ${OPTI} ${DEPS} -I${OINC}  $f  $mylib -lm -o $g 
      if [ -f $k ]
      then 
         ./$g < $k 
      else 
         ./$g
      fi 
      set +x 
   done 
   cd $here 
   unset here 
#
   echo "Done. Leave $dir"
   echo "########################################################################"
}
#


_make_showme ()
{
cat << XXX
USAGE: 
   ${COMP} ${OPTI} ${DEPS} -I${OINC}  main.c $mylib -lm

EXAMPLES:
   ${COMP} ${OPTI} ${DEPS} -I${OINC}  test/xairy.c $mylib -lm
   ./a.out 

XXX

}

_make_clean_prim ()
{
   d=$1; shift;
   if [ -d $d ]
   then 
      echo "Go to ${d}/"
      cd $d 
      echo "   rm -f *.o *.mod *.exe *.a *.out"
      rm -f *.o *.mod *.exe *.a *.out
      echo "Left ${d}/"
   fi 
}  
# 



_make_clean ()
{
   here=`pwd`

   for (( i=0; i<${nDIR}; i++ ))
   do 
      d=${aDIR[$i]}
      _make_clean_prim $d 
      cd $here 
   done 

   for d in $TST
   do
      _make_clean_prim examples/$d 
      cd $here 
   done 

   unset here 
}  
# 

 
_make_distclean () 
{
   _make_clean
   echo "   /bin/rm -rf ${OLIB} ${OINC} ${OOBJ} ${build}"
   /bin/rm -rf ${OLIB} ${OINC} ${OOBJ} ${build}
}
#


_make_src ()
{
   for (( i=0; i<${nSRC}; i++ ))
   do 
      d=${aSRC[$i]}
      mkdir -p ${OOBJ}/${d}
      _make_src_prim $d ${OOBJ}/${d}
   done 
}


_make_src_prim () 
{
   src=$1; shift; 
   out=$1; shift; 
#
   if [ -d "$src" ] 
   then 
      echo "Directory $src exists."
   else 
      echo "Error: Directory $src does not exist!"
      exit 1 
   fi
#
   if [ -d "$out" ] 
   then 
      echo "Directory $out exists."
   else 
      echo "Warning: Directory $out does not exist. Create it!"
   fi
#
   here=`pwd`
#
   echo "########################################################################"
   echo "Compiling *.c inside $src --> $out ..."
#
#  Compiling Fortran codes
#
   cd $src 
   echo "Entering $src ..."
#
#  source codes:
   for f in *.c
   do 
      if [ -f $f ]
      then 
         g=`basename $f`
         h=`echo $g | sed 's/\.c//g'`
         echo "${COMP} ${FLAG} -c  $f  -o ${out}/${h}.o" 
         time  ${COMP} ${FLAG} -c  $f  -o ${out}/${h}.o  
      fi 
   done
#
#  include:
   for f in ${IINC}/*.h 
   do 
      if [ -f $f ]
      then 
         cp -f  $f  ${OINC}/ 
      fi
   done 
#
   cd $here 
   echo "Leaving $src"
#
   unset f here 
   echo "Compiling Done."
   echo "########################################################################"
}
#



_make_lib ()
{
   echo "########################################################################"
   echo "Making ${mylib} "
#
   _make_src 
#
   set -x 
#
   List=''
#
   for (( i=0; i<${nSRC}; i++ ))
   do 
      d=${aSRC[$i]}
      List=" $List ${OOBJ}/${d}/*.o "
   done 

   /bin/rm -rf ${mylib}
   ar  $arFLAG  ${mylib}  $List 

   set +x 

   echo "Done"
   echo "Check *.a in ${OLIB}"
   echo "Check *.h in ${OINC}"
   echo "########################################################################"
}
#


#######################################################################
#
#  main:
#
#######################################################################

#  set -x 

if [ $# -eq 1 ] 
then 
   opt=$1
   if    [ "$opt" = "clean" ]
   then
      _make_clean 
   elif  [ "$opt" = "distclean" ]
   then
      _make_distclean 
   elif  [ "$opt" = "test" ]
   then
      _make_test  
   elif  [ "$opt" = "lib" ] 
   then 
      _make_lib 
   elif  [ "$opt" = "all" ] 
   then 
      _make_clean
      _make_lib
      _make_test 
   elif [ "$opt" = "showme" ]
   then 
      _make_showme 
   else
      _print_usage 
      exit 1 ; 
   fi

elif [ $# -eq 2 ] 
then 

   _make_main_glob $1 $2 

else

   _print_usage 
   exit 1 ; 
fi 

#  set +x 
