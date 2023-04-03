

#include <random>
#include <cstring>
#include <limits>
#include <benchmark/benchmark.h>

extern "C" {
  #include "dgemm.h"
}

using dgemm_t = void (*) (const int m, const int n, const int k, const double *A, const int lda, const double *B, const int ldb, double *C, const int ldc);

// Fill a matrix with random values
static void random_fill(double* A, int size, double range) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-range, range);
    for (int i = 0; i < size; i++) {
        A[i] = dis(gen);
    }
}

static void test_dgemm(benchmark::State& state, dgemm_t dgemm, 
  int m, int n, int k, const double *A, const double *B, double *C) {
    double *C_test = new double[m * n];
    double *C_ref  = new double[m * n];

    std::memcpy(C_test, C, m * n * sizeof(double));
    std::memcpy(C_ref, C, m * n * sizeof(double));

    dgemm(m, n, k, A, k, B, n, C_test, n);
    dgemm_naive(m, n, k, A, k, B, n, C_ref, n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            double diff = std::abs(C_test[i * n + j] - C_ref[i * n + j]);
            if (diff >= std::numeric_limits<double>::epsilon()) {
              state.SkipWithError("GEMM test failed");
              return;
            }
        }
    }

    delete[] C_test;
    delete[] C_ref;
}

static void bm_dgemm(benchmark::State& state, dgemm_t dgemm) {
    int m = state.range(0);
    int n = state.range(1);
    int k = state.range(2);
    
    double *A = new double[m * k];
    double *B = new double[k * n];
    double *C = new double[m * n];
    
    random_fill(A, m * k, 1.0);
    random_fill(B, k * n, 1.0);

    test_dgemm(state, dgemm, m, n, k, A, B, C);
    
    for (auto _ : state) {
        dgemm(m, n, k, A, k, B, n, C, n);
    }
    
    delete[] A;
    delete[] B;
    delete[] C;
}

// Define benchmark cases
#define BENCH_DGEMM(dgemm) \
BENCHMARK_CAPTURE(bm_dgemm, dgemm, dgemm) \
    ->Args({1024, 1024, 1024});

BENCH_DGEMM(dgemm_naive);

// TODO: add dgemm_opt benchmark
// BENCH_DGEMM(dgemm_opt);

BENCHMARK_MAIN();