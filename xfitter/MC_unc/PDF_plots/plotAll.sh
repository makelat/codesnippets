g++ multiplot_MC.cxx $(root-config --cflags --glibs) -std=gnu++0x  -o multiplotEXE
./multiplotEXE
./multiplotEXE 2
./multiplotEXE 3
./multiplotEXE 4
./multiplotEXE 5
./multiplotEXE 6
./multiplotEXE 7
pdflatex all_combined_plots.tex
rm all_combined_plots.aux all_combined_plots.log
