gfortran -c prog.f
g++ -c interface.cxx
mv *.o obj
g++ -o testEXE obj/prog.o obj/interface.o -L/usr/lib/gcc/x86_64-linux-gnu/7 -lgfortran
./testEXE
