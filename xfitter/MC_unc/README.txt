Start from MC_unc.C, and search for "// BEGIN user input". 
This'll take you to the main function.
There, write the path to your central fit's run directory to "central" variable:
this points to where you have steering files and main result that the code will
read as a template, from which to instantiate ~1000 (specify this in nMC) new 
run directories, each with a different random seed. 

Before you read further, I recommend you add a line at the end of your cond.sh 
script (assuming you'll be running these with the Desy HTCondor) that creates a 
dummy text file "finished.txt" at the end of the script -- this way you can 
eventually check which fits have already finished by using checkFinished.sh. At 
least back in the day, condor got grumpy if you ask for the queue too often, so 
this method avoids calling it.

Also, as a word of warning, my old plot code (explained below) is hard-wired 
with a set of Q2 values (always used these, never had an excuse to generalize): 
    1.9 GeV^2, 4 GeV^2, 7 GeV^2, 10 GeV^2, 100 GeV^2, 1k GeV^2, 30k GeV^2
you might want to use the same, or check MCplot.cxx and change this but 
it's quite long


Now, build and run this first code by
    g++ -std=gnu++0x -o MC_uncEXE MC_unc.C
    ./MC_uncEXE

At this point 1000 run directories should have appeared, and the commands to
submit everything to condor (yes this is quite brute force) are written into the
file "submitToHTC_*.sh". Now run the script, thus sending the jobs on their way.

You'll also need to set "centralDir" in MCplot.cxx. 
Again, simply look for "// BEGIN USER INPUT". 
Don't worry about the other paths, these codes are modified based on another 
more general plot script dealing with also other types of plots.

Once all fits are finished, do
  sh plotAll.sh
which compiles and runs the plot codes written in C++, again assuming 7 Q2 
values, so check the number of calls to "./MCplotEXE [number]" 
and "./multiplotEXE [number]" -- the [number] is the index of Q2 value to plot. 
This also produces the file "MC_results.txt", containing the parameter's 
resulting MC uncertainties.

Notice that there are essentially two plot programs: MCplot.cxx in the main 
directory and multiplot_MC.cxx under PDF_plots. The logic here is that MCplot 
produces the individual PDFs as crue plots and saves plots into root objects. 
Then for style setup, just adjust PDF_plots/multiplot_MC.cxx which you can run 
by
    cd PDF_plots
    sh plotAll.sh
This'll also collect all the plots together into a PDF which you can then 
easily scroll through and see if everything is in order.
