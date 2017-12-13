#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "veryBasicMatrix.h"



int main()
{
  unsigned int N = 2000,i,j;
  cMatrix A, B, C;
  init_cMatrix(&A,N);
  init_cMatrix(&B,N);
  init_cMatrix(&C,N);

  double complex omega = cos(2.*M_PI/((double)N)) + I*sin(2.*M_PI/((double)N));
  printf("omega=% 2.1f%+2.1fi \n", creal(omega), cimag(omega));
  double complex omega_i=1., omega_ij=1.;
  
  // A is the Discrete Fourier Transform (DFT) matrix.
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      A.data[i+j*N] = omega_ij;
      omega_ij*=omega_i;
    }
    omega_i*=omega;
  }
  
  // B is A^dag divided by N.
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      B.data[i+j*N] = conj(A.data[j+i*N]) / ((double)N);
    }
  }
  
  printf("\nA=\n"); print_cMatrix(&A);
  printf("\nB=\n"); print_cMatrix(&B);
  
  // A is almost unitary, A and B are constructed in such a way that 
  // C=A*B should be identity:
  cMatrixMatrixMultiplication_good(&A,&B,&C);

  printf("\nC=A*B=\n"); print_cMatrix(&C);

  
  free_cMatrix(&A);
  free_cMatrix(&B);
  free_cMatrix(&C);
  return 0;
}
