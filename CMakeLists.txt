# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("attempt")

set(CMAKE_CXX_STANDARD 11)

# Find Boost and Include it in the program
set(BOOST_ROOT "C:/Program Files/boost/boost_1_68_0")
find_package(Boost 1.68.0)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ENDIF()

# Include sub-projects.
add_subdirectory ("attempt")
