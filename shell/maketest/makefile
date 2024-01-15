CXX=`root-config --cxx`
CXXFLAGS=`root-config --cflags`
LDFLAGS=`root-config --ldflags`
LDLIBS=`root-config --glibs`
ROOTLIBS='-lRooFit'
#The below doesn't work, TODO: find out how to include more libs
#ROOTLIBS='-lRooFit -lHtml -lMinuit -lRooFitCore -lRooStats -lHistFactory'

# The file test.C has to contain the main function

all: test

% : %.C
	g++ -g -Wall `root-config --cflags --libs` -L$(ROOTSYS)/lib $(ROOTLIBS) -L$(ROOTSYS)/include $? -o $@

