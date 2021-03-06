/**
  * @file GPSModule.cpp
  * @author William Teeple
  * @date 12/01/2016
  * Description: GPS Module class
  */

#include "GPSModule.h"

GPSModule::GPSModule(float inLATmin, float inLATmax, float inLONmin, float inLONmax,
                     float outLATmin, float outLATmax, float outLONmin, float outLONmax)
{
  innerWindow = new float[4];
  outerWindow = new float[4];

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
  currDirection = ' '; prevDirection = ' ';

  //initialize default flags
  insideInnerWindow = false;
  outsideOuterWindow = false;

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
  if ((currentCoords[0] >= innerLATmin && currentCoords[0] <= innerLATmax) &&
      (currentCoords[1] >= innerLONmin && currentCoords[1] <= innerLONmax) )
    return true;
  else
    return false;
} // end function checkInnerWindow

bool GPSModule::checkOuterWindow()
{
  if ((currentCoords[0] < outerLATmin || currentCoords[0] > outerLATmax) ||
      (currentCoords[1] < outerLONmin || currentCoords[1] > outerLONmax) )
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

void GPSModule::setCurrAltitude(float alt)
{
  currAltitude = alt;
}

float GPSModule::getPrevAltitude()
{
  return prevAltitude;
}

void GPSModule::setPrevAltitude(float alt)
{
  prevAltitude = alt;
}

char GPSModule::getCurrDirection()
{
  return currDirection;
} // end function getCurrDirection

char GPSModule::getPrevDirection()
{
 return prevDirection;
} // end function getPrevDirection

void GPSModule::updatePosition(std::string newLine)
{

} // end function updatePosition

void GPSModule::writeToScreen(float LAT, float LON, float alt, char direction)
{


} // end function writeToLog

void GPSModule::writeToLog(float LAT, float LON, float alt, char direction)
{
  // log entry template
  // TIME&DATE, LAT: ___, LON: ___, Dir: _, Alt: ___, Radar Statue: On/Off


} // end function writeToLog
