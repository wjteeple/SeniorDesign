/**
  * @file GPSModule.cpp
  * @author William Teeple
  * @date 12/01/2016
  * Description: GPS Module class
  */

#include "GPSModule.h"

GPSModule::GPSModule(float inXmin, float inXmax, float inYmin, float inYmax,
          float outXmin, float outXmax, float outYmin, float outYmax)
{
  innerWindow = new float[4];
  outerWindow = new float[4];

  //set inner window
  innerXmin = innerWindow[0] = inXmin;
  innerXmax = innerWindow[1] = inXmax;
  innerYmin = innerWindow[2] = inYmin;
  innerYmax = innerWindow[3] = inYmax;

  //set outer window
  outerXmin = outerWindow[0] = outXmin;
  outerXmax = outerWindow[1] = outXmax;
  outerYmin = outerWindow[2] = outYmin;
  outerYmax = outerWindow[3] = outYmax;

} // end constructor

GPSModule::~GPSModule()
{
  delete [] outerWindow;
  delete [] innerWindow;
} // end destructor

float* GPSModule::getInnerWindow()
{
  float* test = new float[2];; // [xmin, xmax, ymin, ymax]

  return test;
} // end function getInnerWindow

void GPSModule::setInnerWindow(int* windowCoords)
{

} // end function setInnerWindow

float* GPSModule::getOuterWindow()
{
  float* test = new float[2];

  return test;
} // end function getOuterWindow

void GPSModule::setOuterWindow(int* windowCoords)
{

} // end function setOuterWindow

bool GPSModule::checkInnerWindow()
{
  return false;
} // end function checkInnerWindow


bool GPSModule::checkOuterWindow()
{
  return false;
} // end function checkOuterWindow

float* GPSModule::getCurrentCoords()
{
  float* test = new float[2];

  return test;
} // end function getCurrentCoords

float* GPSModule::getPreviousCoords()
{
  float* test = new float[2];

  return test;
} // end function getPreviousCoords

char GPSModule::getCurrDirection()
{
  return 't';
} // end function getCurrDirection

char GPSModule::getPrevDirection()
{
 return 't';
} // end function getPrevDirection

void GPSModule::updatePosition(std::string newLine)
{

} // end function updatePosition

void GPSModule::writeToLog(float LAT, float LON, float alt, char direction)
{

} // end function writeToLog
