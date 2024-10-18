cmake_minimum_required(VERSION 3.18)
project(PhotonMapping CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# C++ flags o3
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Disable some warnings
add_compile_options(-Wno-stringop-overflow)

# Include directories
include_directories( CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
set(SOURCES ${CPP_SOURCES})

# Add executable
add_executable(photon-mapping ${SOURCES})

# Link libraries
target_link_libraries(photon-mapping PRIVATE)
