/**
  * @file GPSModule.cpp
  * @author William Teeple and Victor Luiz da Silva
  * @date 12/01/2016
  * Description: GPS Module class
  */

#include "GPSModule.h"
#include <iostream>
#include <iomanip>

GPSModule::GPSModule(float inLATmin, float inLATmax, float inLONmin, float inLONmax,
                     float outLATmin, float outLATmax, float outLONmin, float outLONmax)
{
  innerWindow = new float[4];
  outerWindow = new float[4];

  gpsStringCounter = 0;

  //set inner window
  innerLATmin = innerWindow[0] = inLATmin;
  innerLATmax = innerWindow[1] = inLATmax;
  innerLONmin = innerWindow[2] = inLONmin;
  innerLONmax = innerWindow[3] = inLONmax;

  //set outer window
  outerLATmin = outerWindow[0] = outLATmin;
  outerLATmax = outerWindow[1] = outLATmax;
  outerLONmin = outerWindow[2] = outLONmin;
  outerLONmax = outerWindow[3] = outLONmax;

  currentCoords = new float[2];
  previousCoords = new float[2];

  //initialize default positions
  currentLAT = currentCoords[0] = 0.0; currentLON = currentCoords[1] = 0.0;
  previousLAT = previousCoords[0] = 0.0; previousLON = previousCoords[1] = 0.0;
  currAltitude = 0.0; prevAltitude = 0.0;
  currDirectionLAT = ' '; currDirectionLON = ' ';
  prevDirectionLAT = ' '; prevDirectionLON = ' ';

  //initialize default flags
  insideInnerWindow = false;
  outsideOuterWindow = false;

  //initialize default char positions
  latStartPosition = 0;
  lonStartPosition = 0;
  altStartPosition = 0;
  latStringLength = 0;
  lonStringLength = 0;

} // end constructor

GPSModule::~GPSModule()
{
  delete [] outerWindow;
  delete [] innerWindow;
  delete [] currentCoords;
  delete [] previousCoords;
} // end destructor

float* GPSModule::getInnerWindow()
{
  return innerWindow;
} // end function getInnerWindow

void GPSModule::setInnerWindow(float latmin, float latmax, float lonmin, float lonmax)
{
  innerWindow[0] = latmin; innerWindow[1] = latmax;
  innerWindow[2] = lonmin; innerWindow[3] = lonmax;
} // end function setInnerWindow

float* GPSModule::getOuterWindow()
{
  return outerWindow;
} // end function getOuterWindow

void GPSModule::setOuterWindow(float latmin, float latmax, float lonmin, float lonmax)
{
  outerWindow[0] = latmin; outerWindow[1] = latmax;
  outerWindow[2] = lonmin; outerWindow[3] = lonmax;
} // end function setOuterWindow

bool GPSModule::checkInnerWindow()
{
  if ((currentLON >= innerLONmin && currentLON <= innerLONmax) &&
      (currentLAT >= innerLATmin && currentLAT <= innerLATmax) )
    return true;
  else
    return false;
} // end function checkInnerWindow

bool GPSModule::checkOuterWindow()
{
  if ((currentLON >= outerLONmin && currentLON <= outerLONmax) &&
      (currentLAT >= outerLATmin && currentLAT <= outerLATmax) )
    return true;
  else
    return false;
} // end function checkOuterWindow

float* GPSModule::getCurrentCoords()
{
  return currentCoords;
} // end function getCurrentCoords

float* GPSModule::getPreviousCoords()
{
  return previousCoords;
} // end function getPreviousCoords

float GPSModule::getCurrAltitude()
{
  return currAltitude;
}

float GPSModule::getPrevAltitude()
{
  return prevAltitude;
}

void GPSModule::setPrevAltitude(float alt)
{
  prevAltitude = alt;
}

void GPSModule::updatePosition(std::string S)
{
	gpsStringCounter++;
	currentLON = std::stof(S.substr(lonStartPosition,lonStringLength));
	currentLAT = std::stof(S.substr(latStartPosition,latStringLength));
	currDirectionLON = S[lonDirectionPosition];
	currDirectionLAT = S[latDirectionPosition];

/// TO PRINT TO SCREEN:
	std::cout << "\n#" << gpsStringCounter << std::endl;
	std::cout << std::setprecision(12) << currentLAT << " " << currDirectionLAT << " ";
	std::cout << std::setprecision(12) << currentLON << " " <<  currDirectionLON;

}

void GPSModule::writeToLog(float LAT, float LON, float alt, char direction)
{
/**
	TODO: WRITE WRITETOLOG FUNCTION IF REQUIRED
**/
}

void GPSModule::findCoordPositionsInString(std::string s)
{
	latStringLength = -1;
	lonStringLength = -1;
	int count = 0;
	bool pos;

	for (unsigned int i = 0; i < s.length(); i++)
	{
		pos = false;

		if (s[i] == ',')
		{
			count++;
			pos = true;
		}

		switch (count)
		{
			case 2:
				latStartPosition = ((pos) ? i + 1 : latStartPosition);
				latStringLength++;
				break;
			case 3:
				latDirectionPosition = ((pos) ? i+1 : latDirectionPosition);
				break;
			case 4:
				lonStartPosition = ((pos) ? i + 1 : lonStartPosition);
				lonStringLength++;
				break;
			case 5:
				lonDirectionPosition = ((pos) ? i+1 : lonDirectionPosition);
				break;

			//TODO further string extraction -- ALTITUDE?

		}
	}
} // end function findCoordPositionsInString
