/**
  * @file main.cpp
  * @author William Teeple and Victor Luiz da Silva
  * @date 12/01/2016
  * Description: Main driver
  */

#include <iostream>
#include "GPSModule.h"

int main()
{
  std::string test = "$GPGGA,131130.00,6912.4462811,N,04511.5456046,W,1,15,0.69,2660.8587,M,41.6528,M,,*7920161112:131130.968";
  std::cout << "Welcome to your GPS Module!\n\n";

  GPSModule gps(2.0, 3.0, 2.0, 3.0, 1.0, 4.0, 1.0, 4.0);

  //gps.parsePositionString(test);
  gps.updatePosition(test);

  return 0;
}
