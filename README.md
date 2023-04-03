An experiment of dgemm.

## Requirements
CMake 3.1 or above

## Install
```
git submodule update --init --recursive
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release 
cmake --build build -j
```

## Bench Gemm
```
./build/bench_gemm
```

