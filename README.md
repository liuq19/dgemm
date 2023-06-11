# dgemm

An experiment of dgemm.

Requirement:

1. CMake 3.26 or above

Install and Bench:

```
git submodule update --init --recursive
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release 
cmake --build build -j
./build/bench_gemm
```


