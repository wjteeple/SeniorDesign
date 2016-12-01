/**
*	@file : main.cpp
*	@author :  Victor Luiz Berger da Silva
*	@date :  
*/
#include <fstream>
#include <iostream>
#include <string>

bool parse_GPS_string(std::string S);

int main()
{
    std::string fileName, str;

	std::cout << "Enter name of file, or press enter for example. ";
	getline(std::cin, fileName);
	if(fileName.empty()) fileName = "20161107_123249_Test.txt";
	std::ifstream input(fileName);

	if(input.is_open())
	{
		while(getline(input, str))
			parse_GPS_string(str);
		input.close();
	}

    return 0;
}

bool parse_GPS_string(std::string S) 
{
	std::string prefix_match = "$GPGGA";
	if(!S.compare(0, prefix_match.size(), prefix_match))   // Input string starts with "$GPGGA"
	{
		std::cout << "Time: " << S.substr(7, 9)  << std::endl;
		std::cout << "Lat:  " << S.substr(17,12) << " " << S.substr(30,1) << std::endl;
		std::cout << "Long: " << S.substr(32,12) << " " << S.substr(46,1) << std::endl;
		return 1;
	}
	std::cout << std::endl;
	return 0;
}
