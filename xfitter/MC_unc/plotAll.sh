g++ -std=gnu++0x -o computeMC compute_MC_unc.C
./computeMC
g++ MCplot.cxx $(root-config --cflags --glibs) -std=gnu++0x  -o MCplotEXE
./MCplotEXE
./MCplotEXE 2
./MCplotEXE 3
./MCplotEXE 4
./MCplotEXE 5
./MCplotEXE 6
./MCplotEXE 7
cd PDF_plots
g++ multiplot_MC.cxx $(root-config --cflags --glibs) -std=gnu++0x  -o multiplotEXE
./multiplotEXE
./multiplotEXE 2
./multiplotEXE 3
./multiplotEXE 4
./multiplotEXE 5
./multiplotEXE 6
./multiplotEXE 7
pdflatex all_combined_plots.tex
rm all_combined_plots.log all_combined_plots.aux
