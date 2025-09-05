#A simple script to illustrate using pythia8 in python, and illustrating how to optimize
#runtime via parallelization: a single Pythia process takes one thread, but here the goal
#is to run Pythia using several configurations (e.g. different energies and processes...)
#and one thread can take care of one such configuration
#
#Note that Pythia can be installed simply using
#   pip3 install pythia8mc
#or
#   pip3 install pythia8
#depending on your setup
#

#General imports
import numpy as np
import os

#Import tools for parallelization etc
from multiprocessing import Process, Pool, cpu_count
from functools import partial

#Store output into a dataframe
import pandas as pd

#Import Pythia: different users might have different module names in their setup
try: import pythia8
except: import pythia8mc as pythia8

# Generate events for a given configuration
def genEvents(energy,verbose=False):
    pythia = pythia8.Pythia()
    
    # Suppress output
    if not verbose: pythia.readString("Print:quiet = on")
    
    # Read other settings, e.g., to configure a process
    pythia.readString("Beams:eCM = "+energy)
    pythia.readString("HardQCD:all = on")

    # List to store events data for DataFrame
    events_data = []
    
    # Number of MC iterations, event weights
    nevent_mc = 100
    weight = 1./float(nevent_mc) if nevent_mc>0 else 0

    # Initialize Pythia
    pythia.init()
    
    # Event loop
    for ievent in range(nevent_mc):

        # Generate next event
        if not pythia.next(): continue
        
        # Collect all particles in the event
        event_data = []
        
        # loop over particles
        #particles = pythia.process  #"hard"
        particles = pythia.event
        for iparticle, particle in enumerate(particles):
            
            # Reject non-final state particles
            if particle.status() < 0: continue
            
            # Collect particle data
            pid=particle.id()
            px=round(particle.px(),2)
            py=round(particle.py(),2)
            pz=round(particle.pz(),2)
            e =round(particle.e(), 2)
            
            # Store particle
            events_data.append([ievent,iparticle,energy,pid,px,py,pz,e,weight])   
    
    # Even if verbose==False, possible to print statistics at the end
    #pythia.stat()

    # Convert collected event data to DataFrame
    columns = ["ievent","iparticle","truth_energy","pid","px","py","pz","e","weight"]
    df = pd.DataFrame(events_data, columns=columns)  
    
    # Export
    csv_file = "output/events_"+str(energy)+".csv.zip"
    df.to_csv(csv_file, index=False, compression='zip')
    print("Saved "+str(nevent_mc)+" events to file: "+csv_file)
 

if __name__ == '__main__':
    
    # Ensure output destination exists
    if not os.path.exists("output"): os.mkdir("output")
    
    # Run Pythia
    energies = ["7000","13000"]
    N = min(cpu_count(),len(energies))
    runp8 = Pool(processes=N)
    runp8.map(genEvents, energies)
