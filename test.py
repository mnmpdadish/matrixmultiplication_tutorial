
import numpy as np
import time as tm
import sys

def PrettyPrintComplexMatrix(matrix,prec=3,linewidth1=150,suppressOn=True):
  np.set_printoptions(precision=prec,linewidth=linewidth1,suppress=suppressOn)   
  print('RE=\n', np.real(matrix))
  print('Im=\n', np.imag(matrix))
   
def matrixMatrixMultiplication_good(A,B):
  return np.dot(A,B)

def matrixMatrixMultiplication_dummy(A,B):
  N = len(A)
  C = np.zeros((N,N),dtype=complex)
  for ii in range(0,N):
    for jj in range(0,N):
      for kk in range(0,N):
        C[ii,jj] += A[ii,kk]*B[kk,jj]
  return C

N = int(sys.argv[1])
print(N)

A = np.zeros((N,N),dtype=complex)
B = np.zeros((N,N),dtype=complex)

  
omega = np.exp(2.j*np.pi/N)
omega_i  = 1.
omega_ij = 1.

# A is the Discrete Fourier Transform (DFT) matrix.
for ii in range(0,N):
  for jj in range(0,N):
    A[ii,jj] = omega_ij
    B[jj,ii] = np.conj(A[ii,jj])/N
    omega_ij *= omega_i
  omega_i *= omega

print('\nA=\n')
PrettyPrintComplexMatrix(A)
print('\nB=\n')
PrettyPrintComplexMatrix(B)

t1 = tm.time()
C = matrixMatrixMultiplication_good(A,B)

print('\nC=\n')
PrettyPrintComplexMatrix(C)

print('\n\ntime for matrix multiplication: ', tm.time() - t1)

