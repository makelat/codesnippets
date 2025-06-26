#A pytest program illustrating the inclusion of jupyter notebooks in tests. 
#See also the documentation in note.ipynb.
#To run, install pytest and jupyter notebook importer:
#  python3 -m pip install pytest
#  python3 -m pip install import_ipynb
#Then do
#  pytest -v -s test_note.py
#The flags allow for -v=verbose test output, and -s=print std output in terminal while pytest runs

import sys, os
src_path = ""  #"../../"
sys.path.append(src_path)
import pytest
import numpy as np
import import_ipynb
import matplotlib as mpl
mpl.use('Agg')  #Supress GUI output

def notebookRunner(notebook,ref):
    """
    Runs the codes provided in model notebooks, automatizes comparison
    of output energy distributions w/o/ need to run notebooks manually
    Parameters
    ----------
        noteboook: str
            Name of the notebook and the model directory, e.g. "DarkPhoton"
        ref: dict{str: float}
            Expected results
    Returns
    -------
        None
    """

    #Illustrate also creating a symbolic link to the notebook and running via that
    #This is especially handy if (many) test files are organized in a subdirectory,
    #or if many notebooks need to be run (the internal logic operates only using the
    #symlink name here, the actual name of the notebook is just an input parameter)
    #Close/remove existing symlinks/dirs to avoid conflicts
    try:
        print('Removing existing symlinks')
        os.unlink('tmp_notebook.ipynb')
    except:
        print('No existing symlinks detected')

    #Links from the working directory to relevant Model directory
    print('Setting up new symlinks/dirs...')
    os.symlink(src = src_path + notebook + '.ipynb',\
               dst = 'tmp_notebook.ipynb',\
               target_is_directory=False)
    print('...done')

    #Init a tmp file that indicates to the main notebook that pytest is running
    f = open('testRun.txt',"w")
    f.close()

    #Import codes from notebook (symbolic link generalizes import cmd)
    print('Importing notebook...')
    from tmp_notebook import data
    os.remove('testRun.txt')  #Remove the indicator that pytest is running
    print('...done')

    #Verify output against reference values
    assert data==ref  #np.isclose(data,ref)

#Uncomment the below decorator to disable this test
#@pytest.mark.skip
def test_note():
    """
    Main function calls to notebookRunner. 
    Specify the notebooks to be run and the expected values here.
    """

    #Expected numbers of events
    ref = [[x,y] for x in range(2) for y in range(10)]
    
    #Run the notebook, compare output to expectation
    notebookRunner(notebook='note',ref=ref)
