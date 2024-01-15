#Basic usage
#  cmake .
#  make
#./testEXE

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_FORTRAN_COMPILER /usr/bin/gfortran CACHE PATH)
#set(CMAKE_FORTRAN_COMPILER_ENV_VAR /usr/bin/gfortran)

#List languages used throughout the program (could mix C, CXX, Fortran)
project(langmix LANGUAGES CXX) #C Fortran)

add_subdirectory(auxprog)

add_executable(libraryEXE main.cxx)
target_link_libraries(libraryEXE auxlib)
install(TARGETS libraryEXE DESTINATION bin)
