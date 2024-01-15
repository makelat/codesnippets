      subroutine fortprog(n,f)

      implicit none

      integer, intent(in) :: n
      integer :: i
      real(4) :: f
      real(4) :: v(n)

      write(*,*) n, f

      write(*,*) "Testing vector"
      do i = 1,n,1
          v(i) = f*i
          write(*,*) v(i)
      end do

      return
      end
