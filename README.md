# Numerical-Recipes-in-C

This package includes all the source codes of the well-known book:

    Numerical Recipes in C: The Art of Scientific Computing (2nd Edition, 1997)
    by William H. Press, Brian P. Flannery, Saul A. Teukolsky, William T. Vetterling
    
    Software version 2.08
    
    http://numerical.recipes/

Many things have been changed, e.g., all the names of subroutines, so that this version of the code is more portable than the original one.

# How to use? 

You should work in Linux. You need a C compiler, e.g., gcc, icc, and the ar and timeout commands. They can be installed easily.

In Linux terminal, perform the command:

    bash sh.make.dev

Then, read the guide on your screen. 

For example, to run everything, you can run this command:

    bash sh.make.dev  all 

The above command will compile all the codes in src/, prepare the header files, create the library libNRinC.a, compile all programs in test/ and run them right away. 

You can see how to compile and link your program to the library. You can change everything inside the script sh.make.dev.

Enjoy coding!
