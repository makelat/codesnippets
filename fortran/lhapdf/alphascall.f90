!  source setenv.sh
!  gfortran alphascall.f90 -L$LHAPDFLIB -lLHAPDF -o alphascall.out
!  ./alphascall.out
program alphascall

  implicit double precision (a-h,o-z)
  character name*64

  name='ABMP16_5_nlo.LHgrid'
  call initpdfsetbyname(name)
  qmz=91.18d0
  write(*,*)
  call numberpdf(n)
  print *,'There are ',n,' PDF sets'
  write(*,*) 'alpha_S(M_Z) = ',alphaspdf(qmz)

end program alphascall
