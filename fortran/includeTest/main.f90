!!!  gfortran -o hello main.f90
!!!  ./hello

PROGRAM greet

IMPLICIT NONE

INTEGER N
INTEGER M

M=1

PRINT *, "About to check include file"

INCLUDE 'toBeIncluded.h'

PRINT *, "The first number is ",N

M=2

INCLUDE 'toBeIncluded.h'

PRINT *, "The second number is ",N

END PROGRAM greet
