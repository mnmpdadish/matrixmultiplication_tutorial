#pragma once

#include <complex.h>
#include <assert.h>
//#include "../util/utilities.h"

// reminder:
// int * ptr;
// int const * ptrToConst;
// int * const constPtr;
// int const * const constPtrToConst;

// matrix matrix multiplication:
unsigned int zgemm_(char const*, char const*, unsigned int const*, unsigned int const*, unsigned int const*,
                  double complex const*, double complex const*, unsigned int const*, double complex const*, 
                  unsigned int const*, double complex const*, double complex *, unsigned int const*);

#define INIT_CAPACITY 64


typedef struct {
  unsigned int N;
  unsigned int capacity;
  double complex *data;
} cMatrix;

unsigned int resize_cMatrix(cMatrix * A, unsigned int N) {
  while(N*N > A->capacity) A->data = (double complex*) realloc(A->data, (A->capacity *= 2) * sizeof(double complex));
  A->N=N;
  return 0;
}

unsigned int reset_cMatrix(cMatrix * A) {
  unsigned int i;
  for(i=0; i<(A->N*A->N); i++) A->data[i]=0;
  return 0;
}

unsigned int init_cMatrix(cMatrix * A, unsigned int N) {
  A->capacity = INIT_CAPACITY;
  A->data = (double complex *) malloc(A->capacity * sizeof(double complex));
  A->N=N;
  resize_cMatrix(A,N);
  return 0;
}

unsigned int free_cMatrix(cMatrix * A) {
  free(A->data);
  return 0;
}


//C=A*B
unsigned int cMatrixMatrixMultiplication_dummy(cMatrix const * A, cMatrix const * B, cMatrix * C) {
  assert(A->N == B->N);
  resize_cMatrix(C,A->N);
  reset_cMatrix(C); // set matrix to zeros
  unsigned int N=A->N;
  unsigned int i,j,k;
  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      for(k=0;k<N;k++){
        C->data[i+j*N] += A->data[i+k*N] * B->data[k+j*N]; 
      }
    }
  }
  
  return 0;
}


//C=A*B
unsigned int cMatrixMatrixMultiplication_good(cMatrix const * A, cMatrix const * B, cMatrix * C) {
  assert(A->N == B->N);
  resize_cMatrix(C,A->N);
  unsigned int N=A->N;
  double complex one=1.0;
  double complex zero=0.0;
  char no = 'n';
  zgemm_(&no,&no,&N,&N,&N, &one, A->data, &N, B->data, &N, &zero, C->data, &N); 
  return 0;
}



unsigned int print_cMatrix(cMatrix const * A) {
  if (!A){ 
    printf("oups.\n");
    return -1;
  }
  
  unsigned int i,j, isLarge=1;
  unsigned int nPrint=10;
  if(A->N <nPrint) {
    nPrint=A->N;
    isLarge=0;
  }
  double complex val;
  double tol=0.00001;

  for (i = 0; i < nPrint; i++) {
    for (j = 0; j < nPrint; j++) {
      val = A->data[i+j*A->N];
      if(cabs(val)>tol) printf("% 2.1f%+2.1fi ", creal(val), cimag(val));
      else  printf("    .     ");
    }
    if(isLarge) printf("   ...");
    printf("\n");
  }
  if(isLarge) {
    for (i = 0; i < nPrint+1; i++) printf("   ...    ");
    printf("\n");
  }
  
  fflush(stdout);
  return 0;
}

