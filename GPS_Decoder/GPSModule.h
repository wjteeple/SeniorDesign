/**
  * @file GPSModule.h
  * @author William Teeple
  * @date 12/01/2016
  * Description: Header file for GPS Module class
  */

#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <string>

class GPSModule
{
public:
  /**
    *	@pre : None
    *	@post : Creates an object of type GPSModule with start coordinates set
    *	@return : None
    */
  GPSModule(float inLATmin, float inLATmax, float inLONmin, float inLONmax,
            float outLATmin, float outLATmax, float outLONmin, float outLONmax);

  /**
    *	@pre : None
    *	@post : Destructs the given GPSModule object
    *	@return : None
    */
  ~GPSModule(); //redundant

  /**
    *	@pre : Exising GPSModule with initialized inner window coordinates
    *	@post : None
    *	@return : An array containing the inner window coords [xmin, xmax, ymin, ymax]
    */
  float* getInnerWindow();

  /**
    *	@pre : Existing GPSModule, input array [xmin, xmax, ymin, ymax]
    *	@post : Sets all values of the inner window
    *	@return : None
    */
  void setInnerWindow(float latmin, float latmax, float lonmin, float lonmax);

  /**
    *	@pre : Exising GPSModule with initialized outer window coordinates
    *	@post : None
    *	@return : An array containing the outer window coords [xmin, xmax, ymin, ymax]
    */
  float* getOuterWindow();

  /**
    *	@pre : Existing GPSModule, input array [xmin, xmax, ymin, ymax]
    *	@post : Sets all values of the outer window
    *	@return : None
    */
  void setOuterWindow(float latmin, float latmax, float lonmin, float lonmax);

  /**
    *	@pre : Existing GPSModule, inner window coords set
    *	@post : None
    *	@return : Returns true if the current coords are within the inner window, false otherwise
    */
  bool checkInnerWindow();

  /**
    *	@pre : Existing GPSModule, outer window coords set
    *	@post : None
    *	@return : Returns true if the current coords are outside the outer window, false otherwise
    */
  bool checkOuterWindow();

  /**
    *	@pre : Existing GPSModule, current coords set
    *	@post : None
    *	@return : Returns an array of the current LAT and LON, format [LAT, LON]
    */
  float* getCurrentCoords();

  /**
    *	@pre : Existing GPSModule, previous coords set
    *	@post : None
    *	@return : Returns an array of the previous LAT and LON, format [LAT, LON]
    */
  float* getPreviousCoords();

  /**
    *	@pre : Existing GPSModule, current altitude set
    *	@post : None
    *	@return : Returns the current altitude
    */
  float getCurrAltitude();

  /**
    *	@pre : Existing GPSModule
    *	@post : Sets the current altitude
    *	@return : None
    */
  void setCurrAltitude(float alt);

  /**
    *	@pre : Existing GPSModule, previous altitude set
    *	@post : None
    *	@return : Returns athe previous altitude
    */
  float getPrevAltitude();

  /**
    *	@pre : Existing GPSModule
    *	@post : Sets the previous altitude
    *	@return : None
    */
  void setPrevAltitude(float alt);

  /**
    *	@pre : Existing GPSModule, current direction set
    *	@post : None
    *	@return : Returns a character that correspondes to the current direction
    */
  char getCurrDirection();

  /**
    *	@pre : Existing GPSModule, previous direction set
    *	@post : None
    *	@return : Returns a character that correspondes to the previous direction
    */
  char getPrevDirection();

  /**
    *	@pre : Existing GPSModule, string to decode
    *	@post : Decodes string and updates current and previous LAT and LON, altitude, and direction
    *	@return : None
    */
  void updatePosition(std::string S);

  /**
    *	@pre : Existing GPSModule, current data variables initialized
    *	@post : Outputs to a text file, storing LAT, LON, direction, altitude, and time (perhaps gradient?)
    *	@return : None
    */
  void writeToLog(float LAT, float LON, float alt, char direction);
  
  void parsePositionString(std::string S);

private:
  //location variables
  float currentLON, currentLAT, previousLON, previousLAT; // current and previous coords
  float* currentCoords;
  float* previousCoords;

  float currAltitude, prevAltitude; //current altitude
  char currDirectionLAT, currDirectionLON, prevDirectionLAT, prevDirectionLON; // current direction

  //window variables
  float innerLATmin, innerLATmax, innerLONmin, innerLONmax; // inner window mins/maxs
  float outerLATmin, outerLATmax, outerLONmin, outerLONmax; // outer window mins/maxs
  float* innerWindow; // [xmin, xmax, ymin, ymax]
  float* outerWindow; // [xmin, xmax, ymin, ymax]

  //flags
  bool insideInnerWindow; // flag for entering the inner window
  bool outsideOuterWindow; // flag for leaving the outer window
};

#endif
