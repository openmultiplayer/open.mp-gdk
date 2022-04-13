cmake_minimum_required(VERSION 3.19)
project(omp-gdk LANGUAGES C CXX VERSION 0.0.1)

file(GLOB_RECURSE omp_gdk_source_list "*.hpp" "*.cpp")

add_library(omp-gdk STATIC ${omp_gdk_source_list})

target_link_libraries(omp-gdk PUBLIC
    OMP-SDK
)

set(OMP_GDK_PATH ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(omp-gdk INTERFACE "")
