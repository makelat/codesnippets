#Make sure pytest is installed:
#  python3 -m pip install pytest

import pytest

#Define a function
def divide(a,b):
    return a/b

#To run this test program, do
#  pytest unit_tests.py
#Uncomment the below decorator to disable this test
#@pytest.mark.skip
def test_divide():
    
    #Check example cases
    assert divide(a=4,b=2)==2
    assert divide(a=-1,b=5)==-0.2
    
    #Expect a certain kind of error
    with pytest.raises(ZeroDivisionError):
        divide(a=137,b=0)
    
