cmake_minimum_required(VERSION 3.20)
project(EC-DE VERSION 1.0 LANGUAGES CXX)

# C++17 cho structured bindings và std::filesystem
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type mặc định là Release nếu không chỉ định
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -O2)
endif()

# ── Thư viện chung (shared library cho tất cả executables) ──────────────────
add_library(core STATIC
    src/benchmark.cpp
    src/de.cpp
    src/ga.cpp
    src/utils.cpp
)

target_include_directories(core PUBLIC include)

# ── Executables ──────────────────────────────────────────────────────────────
add_executable(run_main      experiments/main.cpp)
add_executable(run_compare   experiments/exp_compare.cpp)
add_executable(run_params    experiments/exp_params.cpp)

# Link tất cả executables với core library
foreach(target run_main run_compare run_params)
    target_link_libraries(${target} PRIVATE core)
endforeach()

# ── Output vào thư mục riêng cho gọn ─────────────────────────────────────────
set_target_properties(run_main run_compare run_params
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)