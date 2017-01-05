GPSDriver: main.o GPSModule.o 
	g++ -g -Wall -std=c++11 main.o GPSModule.o -o GPSDriver

main.o: main.cpp GPSModule.h
	g++ -g -Wall -std=c++11 -c main.cpp

GPSModule.o: GPSModule.h GPSModule.cpp
	g++ -g -Wall -std=c++11 -c GPSModule.cpp

clean:
	rm *.o GPSDriver
