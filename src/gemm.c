#include "gemm.h"

// row-major storing for matrices A, B, C.
#define A(i,j) A[(i)*lda + (j)]
#define B(i,j) B[(i)*ldb + (j)]
#define C(i,j) C[(i)*ldc + (j)]

// GEMM function.
// C = alpha * A x B + beta * C, for matrices A, B, C.
// lda, ldb, ldc is the leading dimension of A, B, C.
// Matrix is raw-major storing here.
void gemm_native(const double *A, const double *B, double *C,  const int m, const int n, const int k, 
        const double alpha, const double beta, const int lda, const int ldb, const int ldc) {
    int i, j, kk;
    double dot;

    for (i = 0; i < m; ++i){
        for (j = 0; j < n; ++j){
            dot = 0;
            for (kk = 0; kk < k; ++kk){
                dot += A(i, kk) * B(kk, j);
            }
            C(i, j) = alpha * dot + beta * C(i, j);
	    }
    }
}

// TODO: implement me
// void gemm_opt(const double *A, const double *B, double *C, const int m, const int n, const int k, 
//         const double alpha, const double beta, const int lda, const int ldb, const int ldc) {
// }
