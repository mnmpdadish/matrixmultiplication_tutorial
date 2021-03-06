# README #

Programmer:  Maxime Charlebois

This code is a tutorial to show how useful MKL is compared to LAPACK or an even
simpler algorithm. I calculate a matrix matrix multiplication. The matrices chosen
are the matrices of the Discrete Fourier Transform (DFT). 
See: https://en.wikipedia.org/wiki/DFT_matrix

It is easy to generate automatically for any size of system and we know that it
is a unitary matrix. Hence, if we multiply it by its hermitian conjugate, it 
should give the identity matrix (easy to check). The result does not matter here
(it is only useful to check if the computation yield the correct output). What
matter here is the speed of the matrices multiplication.

## MAIN REPOSITORY:

To get the most recent version of the source code on this project,
in command line on a bash terminal (represented here with the "$" sign), type:

$ git clone https://github.com/mnmpdadish/matrixmultiplication_tutorial.git


## COMPILING:

to compile, go in the "matrixmultiplication_tutorial" directory (where the "makefile" is) and type:

```
$ make
```

There is 3 ways to compile this code:

1. using the "cMatrixMatrixMultiplication_dummy" function.
2. using the "cMatrixMatrixMultiplication_good" function linked with lapack
3. using the "cMatrixMatrixMultiplication_good" function linked with mkl

In any case, you need at least lapack or mkl installed so that the function
"cMatrixMatrixMultiplication_good" compile (unless you do not use it and you
comment it in the ".h"). To choose between the 3 choices, you need to either
edit the "main.c" and choose which "cMatrixMatrixMultiplication" function to use
and/or edit the "makefile" to choose which "LIBS" variable to use.


## DEPENDENCIES:

To compile, the system need the compiler gcc and a valid version of lapack and/or mkl.

MKL:      https://software.intel.com/en-us/mkl
lapack:   http://www.netlib.org/lapack/

Tested with gcc-5.4, lapack-3.8.0 and l_mkl_2018.0.128. Should work with any version.


## RUN:

To run the code with a matrix 10 by 10, type:

```
$ ./test 10
```

The number choose the matrix size.

Running the program gives you the following output. It print matrices A, B and C.
A is the DFT matrix (times srqt(N) where N is the size of the matrix), B is the 
hermitian conjugate of A (divided by N) and C should be the identity. If the 
matrix is too big, it print only the first 10x10 block. 

Depending on the chosen way to compile the code, the time it take to compute 
a matrix multiplication with size=2000 on my machine is:

method 1. (dummy):  3m36.160s
method 2. (lapack): 0m8.628s
method 3. (MKL):    0m4.666s

note that to obtain a good comparison between different methods, I had to do:

```
$ export OMP_NUM_THREADS=1
```

in order to enforce lapack and mkl to use only one processor (otherwise it is unfair).
If you change the size of the matrix, you can check that the algorithm scale as O(n^3).

####

To compare with python, there is a "test.py". To run, install python and numpy and type:
$ python test.py 10

The philosophie is the same here. There is two possible function:
1. "matrixMatrixMultiplication_dummy" which use 3 for loops, and 
2. "matrixMatrixMultiplication_good", which use numpy.dot function.

According to my test with N=1000:
method 1. (dummy) 19 minutes
method 2. (numpy) 1.02 secondes

Hence, on my machine at least, python+numpy has the same performance as c+lapack. 
It is possible to compile numpy with mkl, but this is not covered here.

Here mkl is clearly the winner.

