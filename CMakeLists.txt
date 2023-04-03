cmake_minimum_required(VERSION 3.1)
project(SIMDTour)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add google benchmark
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(thirdparty/benchmark)

add_library(dgemm SHARED src/dgemm.c)
target_include_directories(dgemm PUBLIC include/)
target_compile_options(dgemm PRIVATE -Wall -Werror -Wextra -O3 -g) 

add_executable(bm_dgemm bm_dgemm.cpp)
target_compile_options(bm_dgemm PRIVATE -march=native -O3 -Wall -Wextra -Werror -g)
target_link_libraries(bm_dgemm PRIVATE dgemm benchmark::benchmark)