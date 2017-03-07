/**
  * @file main.cpp
  * @author William Teeple and Victor Luiz da Silva
  * @date 12/01/2016
  * Description: Main driver
  */

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string>
#include "GPSModule.h"

int main(int argc,  char** argv)
{
	float latInMin=1, latInMax=1, lonInMin=1, lonInMax=1, latOutMin=1, latOutMax=1, lonOutMin=1, lonOutMax =1;

	//program initialization
        std::cout << std::endl << "Welcome to GPS test program!\n";

        if(argc == 9)
        {
            latInMin = std::stof(argv[1]);
            latInMax = std::stof(argv[2]);
            lonInMin = std::stof(argv[3]);
            lonInMax = std::stof(argv[4]);
            latOutMin = std::stof(argv[5]);
            latOutMax = std::stof(argv[6]);
            lonOutMin = std::stof(argv[7]);
            lonOutMax = std::stof(argv[8]);
        }
				else if(argc == 2) // User passed in a text-file input
				{
					std::string filename = argv[1];
					std::ifstream myFile(filename);
					if(myFile.is_open())
						std::cout << "Using input from file " << filename << std::endl;
					else
					{
						std::cout << "Unable to open file, try again." << std::endl;
						return 1;
					}

					std::string latInMinStr, latInMaxStr, lonInMinStr, lonInMaxStr;
					std::string latOutMinStr, latOutMaxStr, lonOutMinStr, lonOutMaxStr;

					myFile >> latInMinStr >> latInMaxStr >> lonInMinStr >> lonInMaxStr >> latOutMinStr >> latOutMaxStr >> lonOutMinStr >> lonOutMaxStr;

					latInMin = std::stoi(latInMinStr);
					latInMax = std::stoi(latInMaxStr);
					lonInMin = std::stoi(lonInMinStr);
					lonInMax = std::stoi(lonInMaxStr);
					latOutMin = std::stoi(latOutMinStr);
					latOutMax = std::stoi(latOutMaxStr);
					lonOutMin = std::stoi(lonOutMinStr);
					lonOutMax = std::stoi(lonOutMaxStr);

					std::cout << "Window coordinates being used:  ";
					std::cout << latInMin << " " << latInMax << " " << lonInMin << " " << lonInMax;
					std::cout << " " << latOutMin << " " << latOutMax << " " <<  lonOutMin << " " << lonOutMax << std::endl;

				}
        else if(argc == 1)
        {
            std::cout << "No run-time arguments detected.\n\nEnter inner window latitude MIN: "; std::cin >> latInMin;
            std::cout << "Enter inner window latitude MAX: "; std::cin >> latInMax;
            std::cout << "Enter inner window longitude MIN: "; std::cin >> lonInMin;
            std::cout << "Enter inner window longitude MAX: "; std::cin >> lonInMax;
            std::cout << "Enter outer window latitude MIN: "; std::cin >> latOutMin;
            std::cout << "Enter outer window latitude MAX: "; std::cin >> latOutMax;
            std::cout << "Enter outer window longitude MIN: "; std::cin >> lonOutMin;
            std::cout << "Enter outer window longitude MAX: "; std::cin >> lonOutMax;
        }
        else
        {
            std::cout << "Incorrect command-line arguments, please run program again.\n";
            std::cout << "Expected input: \nlatInMin latInMax lonInMix lonInMax latOutMin latOutmax lonOutMin lonOutMax" << std::endl;
            return 1;
        }


	//open serial input for GPS device
	// /dev/ttyS0
	int gpsSerial = open("/dev/ttyUSB0", O_RDONLY);

	if (gpsSerial == -1)
	{
		std::cerr << "Failed to open port to GPS. Exiting...\n\n";
		exit(EXIT_FAILURE);
	}

	//initialize GPS handler
	GPSModule gps(latInMin, latInMax, lonInMin, lonInMax, latOutMin, latOutMax, lonOutMin, lonOutMax);

	char c = ' ';
	std::string gpsString = "";

	do
	{
		//read in each character
		read(gpsSerial, &c, 1);
		//check for new GPS string
		if (c == '$')
		{
			if (gpsString.find('$') != std::string::npos)
			{
				if(gps.gpsStringCounter % 5 == 0)
					gps.findCoordPositionsInString(gpsString);
				gps.updatePosition(gpsString);
                                std::cout << std::endl;
                                if(gps.checkInnerWindow())
                                    std::cout << "INSIDE INNER WINDOW, ";
                                else
                                    std::cout << "OUTSIDE INNER WINDOW, ";
                                if(gps.checkOuterWindow())
                                    std::cout << "INSIDE OUTER WINDOW\n";
                                else
                                    std::cout << "OUTSIDE OUTER WINDOW\n";
			}
			gpsString = "$";
		}
		else if (isprint(c))
		{
			gpsString += c;
		}

	} while(1);

	close(gpsSerial);

	return 0;
}
