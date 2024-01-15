!  source setenv.sh
!  gfortran lhapdfcall.f90 -L$LHAPDFLIB -lLHAPDF -o lhapdfcall.out
!  ./lhapdfcall.out
program lhapdfcall
  implicit double precision (a-h,o-z)
  character name*64
  double precision f(-6:6)
  character*20 lparm
  logical has_photon
  dimension z(10), xx(10)
  Data (z(i), i=1,10) /.05, .1, .2, .3, .4, .5, .6, .7, .8, .9/
  Do i = 1, 10
     xx(i) = z(i) **3
  EndDo
  name='ABMP16_5_nlo.LHgrid'
  call initpdfsetbyname(name)
  qmz=91.18d0
  write(*,*)
  call numberpdf(n)
  print *,'There are ',n,' PDF sets'
  do i=0,n
     write(*,*) '---------------------------------------------'
     call initpdf(i)
     write(*,*) 'PDF set ',i
     call getxmin(i,xmin)
     call getxmax(i,xmax)
     call getq2min(i,q2min)
     call getq2max(i,q2max)
     print *,'xmin=',xmin,' xmax=',xmax,' Q2min=',q2min,' Q2max=',q2max
     call getminmax(i,xmin,xmax,q2min,q2max)
     print *,'xmin=',xmin,' xmax=',xmax,' Q2min=',q2min,' Q2max=',q2max
     call setlhaparm('EXTRAPOLATE') 
     call getlhaparm(18,lparm) 
     print *,'lhaparm(18)=',lparm
     write(*,*)
     a=alphaspdf(qmz)
     write(*,*) 'alpha_S(M_Z) = ',a
     call getlam4m(1,i,xlam4)
     call getlam5m(1,i,xlam5)
     print *,' lambda5: ',xlam5, ' lambda4: ',xlam4
     write(*,*)
     write(*,*) 'x*up'
     write(*,*) '   x     Q=10 GeV     Q=100 GeV    Q=1000 GeV'
     ! q2 = 10.0d0
     ! q = dsqrt(q2)
     q = 50.0d0
     print *,q
     do ix=1,10
        ! x = (ix-0.5d0)/10.0d0
        x = xx(ix)
        ! x = z(ix)
        if(has_photon()) then
          print *,"This set has a photon"
          call evolvepdfphoton(x,q,f,photon)
        else
          call evolvepdf(x,q,f)
        endif
        g = f(0)
        u = f(2)
        d = f(1)
        write(*,'(F7.4,13(1pE10.3))') x,u,d,g
     enddo
  enddo
end program lhapdfcall
