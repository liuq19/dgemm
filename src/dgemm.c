#include "dgemm.h"

// row-major storing for matrices A, B, C.
#define A(i,j) A[(i)*lda + (j)]
#define B(i,j) B[(i)*ldb + (j)]
#define C(i,j) C[(i)*ldc + (j)]

// GEMM function.
// C = A x B + C, for matrices A, B, C.
// lda, ldb, ldc is the leading dimension of A, B, C.
// Matrix is raw-major storing here.
void dgemm_naive(const int m, const int n, const int k, const double *A, const int lda, const double *B, const int ldb, double *C, const int ldc) {
    int i, j, kk;
    double dot;

    for (i = 0; i < m; ++i){
        for (j = 0; j < n; ++j){
            dot = 0;
            for (kk = 0; kk < k; ++kk){
                dot += A(i, kk) * B(kk, j);
            }
            C(i, j) += dot;
	    }
    }
}

// TODO: implement me
// void dgemm_opt(const int m, const int n, const int k, const double *A, const int lda, const double *B, const int ldb, double *C, const int ldc)
