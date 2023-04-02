# Numerical-Recipes-in-C

This package includes all the source codes of the well-known book:

    Numerical Recipes in C: The Art of Scientific Computing (2nd Edition, 1997)
    by William H. Press, Brian P. Flannery, Saul A. Teukolsky, William T. Vetterling
    
    Software version 2.08
    
    http://numerical.recipes/

Many things have been changed, e.g., all the names of subroutine. This version of the code is more portable than the original one.

# How to use? 

It works in Linux. 

You need a C compiler, e.g., **gcc** or **icc**. You also need the **ar** and **timeout** commands, where **timeout** is only for running tests.

In Linux terminal, perform the command:

    bash sh.make.dev

Then, read the guide on your screen. 

For example, to run everything, you can do like this:

    bash sh.make.dev  all 

The latter command compiles all the codes in **src/**, prepares the header files, i.e., **src/\*.h**, creates the library **libNRinC.a**, compiles all programs in **test/** and excecutes them right away. 

You can see how to compile and link your program to the library. You can change everything inside the script **sh.make.dev**.

One more thing: all real numbers are compiled with double precision (i.e., 8 bytes, double) instead of single precision (4 bytes, float) as in the original version. Make your own setting in **src/nrc_types.h**.

Enjoy coding!

Minor notes:
-------------

(1) For the command:

    timeout

    To run a command with a time limit. More information: <https://www.gnu.org/software/coreutils/timeout>. 

In case you dont have it, install it by one of the following:

    Debian      apt-get install coreutils 
    Ubuntu      apt-get install coreutils 
    Arch Linux  pacman -S coreutils 
    CentOS      yum install coreutils 
    OS X        brew install coreutils 

Ref.:
    https://command-not-found.com/timeout

(2) ...
