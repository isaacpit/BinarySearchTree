CXX = g++ 
CXXFLAGS = -std=c++14

targ = main

main: main.cpp
	fltk-config  --compile  main.cpp

old: main.o
	$(CXX) $(CXXFLAGS) -o $(targ) $(targ).o

main.o: main.cpp Btree.h
	$(CXX) $(CXXFLAGS) -c $(targ).cpp 

clean: 
	rm *.o
	rm main