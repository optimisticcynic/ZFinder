# Pull in ROOT
ROOT_INCLUDES=`root-config --cflags`
ROOT_ALL=`root-config --cflags --libs`
ROO_INCLUDES=${ROOT_ALL} -I${ROOFITSYS}/include -L${ROOFITSYS}/lib -lRooFit -lRooFitCore -lRooStats

#Compiler
CC=g++ -O2 -g -std=c++0x -Wall
CCC=${CC} -c

all: MomPDFPlots.exe MomRapidityPDFPlots.exe FitPDFPlots.exe

%.exe: %.cpp
	${CC} ${ROOT_ALL} ${ROO_INCLUDES} -o $@ $< 

%.o:%.cpp %.h
	${CCC} ${ROOT_INCLUDES} $< -o $@

clean:
	rm -f MomPDFPlots.exe *.o
