#Usage:
#  cd build
#  cmake ..
#  cmake --build .
#  cd ../run
#  ./run

cmake_minimum_required(VERSION 3.10)

project(CRT VERSION 1.0.0)

add_subdirectory(libs)
add_subdirectory(app)
