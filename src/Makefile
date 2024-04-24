main.exe: *.cc
	g++ -std=c++17 -o main.exe main.cc

#%.exe:
#	g++ -o @.exe @.cc

#IsoGraph.o: IsoGraph.cc Classification.o utils.o
#	g++ -c IsoGraph.cc

#Classification.o: Classification.cc utils.o
#	g++ -c Classification.cc

utils.o: utils.cc
	g++ -c utils.cc

clean:
	-del -f *.o 
	-del -f *.exe