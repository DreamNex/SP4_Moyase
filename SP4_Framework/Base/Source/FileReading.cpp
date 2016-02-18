#include <iostream>
#include <sstream>
#include "FileReading.h"

FileReading::FileReading()
{

}

FileReading::~FileReading()
{

}

// Be abl to open any text file you want and store it into a vector
void FileReading::loadVariables(std::string filename, bool unlock, int tool[3])
{
	char commas;
	std::ifstream myfile;
	myfile.open(filename);
	std::string line;
	storage.clear();

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::istringstream ss(line);
			storage.push_back(line);
		}
	}

	myfile.close();
	
	if (storage.at(0) == "true")
	{
		unlock = true;
	}
	else if (storage.at(0) == "false")
	{
		unlock = false;
	}
	
	std::stringstream splitter(storage.at(1));
	std::string token;
	
	while (std::getline(splitter, token, ','))
	{
		
		for (int i = 0; i != 3; i++)
		{
			tool[i] = atoi(token.c_str);
		}
	}
}