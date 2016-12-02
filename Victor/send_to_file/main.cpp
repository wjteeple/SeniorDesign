/**
*	@file : main.cpp
*	@author :  Victor Luiz Berger da Silva
*	@date :  Dec 1, 2016
*
*	Parses GPS text input, separates TIME/LAT/LONG information.
*	Produces new text output file with name "..._result.txt"
*/
#include <fstream>
#include <iostream>
#include <string>

std::string fileName, prefix_match;
std::ofstream outFile;
int counter;
bool parse_GPS_string(std::string S);

int main(int argc, const char * argv[])
{
	counter = 1;
	prefix_match = "$GPGGA";
    	std::string str;
	char yesOrNo;
	if(argc>1)fileName = argv[1];
	else 
	{
		std::cout << "Run-time argument not found. Proceed with default test file? [y/n] ";
		std::cin >> yesOrNo;
		if (yesOrNo == 'y' || yesOrNo =='Y') fileName = "20161107_123249_Test.txt";
		else if (yesOrNo == 'n' || yesOrNo == 'N') 
		{
			std::cout << "Enter desired file name: ";
			std::cin >> fileName;
		}
		else
		{
			std::cout <<"ERROR: Command not recognized, exiting program.\n";
			return 1;			
		}
	}
	std::ifstream input(fileName);
	if(!input.is_open() || input.fail()) 
	{
		std::cout << "ERROR: File not found, exiting program.\n";
		return 1;
	}	
	fileName.erase(fileName.end()-4,fileName.end());
	std::string finalName = fileName.append("_result.txt");
	outFile.open(finalName);
	while(getline(input, str))
		parse_GPS_string(str);
	input.close();
	std::cout << "Input successfully parsed to " << finalName << ". Exiting program.\n";
    	return 0;
}

bool parse_GPS_string(std::string S) 
{
	if(!S.compare(0, prefix_match.size(), prefix_match))   // Input string starts with "$GPGGA"
	{
		outFile << counter <<"\r\nTime: " << S.substr(7, 9)  << "  ";
		outFile << "Lat: "  << S.substr(17,12) << " " << S.substr(30,1) << "  ";
		outFile << "Long: " << S.substr(32,12) << " " << S.substr(46,1) << "\r\n";
		outFile << "\r\n";
		++counter;
		return 1;
	}
	return 0;
}
