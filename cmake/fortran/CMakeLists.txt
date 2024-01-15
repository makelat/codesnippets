#Tell cmake where the source files and CMakeLists.txt are. In this case, here.
#  cmake .

#The above command created a makefile (when running Linux), build and run by:
#  make
#  ./greet

#enable_language(FORTRAN)

cmake_minimum_required(VERSION 3.10)

#List languages used throughout the program (could mix C, CXX, Fortran)
# N.B. THIS IS CASE SENSITIVE! E.g. "FORTRAN" or "fortran" wont work
project(hello LANGUAGES Fortran)

#set(ENV{CMAKE_FORTRAN_COMPILER_ENV_VAR} /usr/bin/gfortran)

#Creates executable "greet" from src code in hello.cxx
add_executable(greet hello.f90)
