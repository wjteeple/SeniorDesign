/**
  * @file main.cpp
  * @author William Teeple
  * @date 12/01/2016
  * Description: Main driver
  */

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include "GPSModule.h"

int main()
{
	float latInMin, latInMax, lonInMin, lonInMax, latOutMin, latOutMax, lonOutMin, lonOutMax;

	//program initialization
	std::cout << "Welcome to GPS test program!\n";
	std::cout << "Enter inner window latitude MIN: "; std::cin >> latInMin;
	std::cout << "Enter inner window latitude MAX: "; std::cin >> latInMax;
	std::cout << "Enter inner window longitude MIN: "; std::cin >> lonInMin;
	std::cout << "Enter inner window longitude MAX: "; std::cin >> lonInMax;
	std::cout << "Enter outer window latitude MIN: "; std::cin >> latOutMin;
	std::cout << "Enter outer window latitude MAX: "; std::cin >> latOutMax;
	std::cout << "Enter outer window longitude MIN: "; std::cin >> lonOutMin;
	std::cout << "Enter outer window longitude MAX: "; std::cin >> lonOutMax;
	
	//initialize GPS handler
	GPSModule gps(latInMin, latInMax, lonInMin, lonInMax, latOutMin, latOutMax, lonOutMin, lonOutMax);

	//open serial input for GPS device
	int gpsSerial = open("/dev/ttyS0", O_RDONLY);
	char c = ' ';	
	std::string gpsString = "";

	do
	{
		//read in each character
		read(gpsSerial, &c, 1);

		//check for new GPS string
		if (c == '$')
		{
			if (gpsString != "")
			{
				std::cout << gpsString;
				gps.updatePosition(gpsString);
			}
			gpsString = "$";
		}
		else
		{
			gpsString += c;
		}
		
	} while(true);

	return 0;
}
