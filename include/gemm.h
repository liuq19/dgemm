
void gemm_native(const double *A, const double *B, double *C,  const int m, const int n, const int k, 
        const double alpha, const double beta, const int lda, const int ldb, const int ldc);

void gemm_opt(const double *A, const double *B, double *C,  const int m, const int n, const int k, 
        const double alpha, const double beta, const int lda, const int ldb, const int ldc);
