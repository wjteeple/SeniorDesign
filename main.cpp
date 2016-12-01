/**
  * @file main.cpp
  * @author William Teeple
  * @date 12/01/2016
  * Description: Main driver
  */

#include <iostream>
#include "GPSModule.h"

int main()
{
  std::cout << "Welcome to your GPS Module!\n\n";
  
  GPSModule gps(2.0, 3.0, 2.0, 3.0, 1.0, 4.0, 1.0, 4.0);

  return 0;
}
