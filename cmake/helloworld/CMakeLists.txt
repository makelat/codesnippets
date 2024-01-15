cmake_minimum_required(VERSION 3.10)

#List languages used throughout the program (could mix C, CXX, FORTRAN)
project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#Creates executable "greet" from src code in hello.cxx
add_executable(greet hello.cxx)

#Tell cmake where the source files and CMakeLists.txt are. In this case, here.
#  cmake .

#The above command created a makefile (when running Linux), build and run by:
#  make
#  ./greet

#Clean:
#  rm -rf CMakeFiles
#  rm CMakeCache.txt cmake_install.cmake greet Makefile Makefile.tmp
