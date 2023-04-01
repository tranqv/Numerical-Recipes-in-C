

for f in `ls *.c` ; do set -x ; gcc -ansi -O3 -c $f ; set +x ; done 

set -x 

ar rcs libnrc.a  *.o 
rm *.o 

set +x 
