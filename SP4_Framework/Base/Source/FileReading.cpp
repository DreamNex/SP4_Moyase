#include <iostream>
#include <sstream>
#include "FileReading.h"

FileReading::FileReading()
{

}

FileReading::~FileReading()
{

}

void FileReading::Init()
{

}
// Be abl to open any text file you want and store it into a vector
std::vector<std::string> loadVariables(std::vector<std::string> &storage, std::string filename)
{
	std::ifstream myfile;
	myfile.open(filename);
	std::string line;

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::istringstream ss(line);
			storage.push_back(line);
		}
	}

	myfile.close();

	std::vector<char> var(storage.begin(), storage.end());
	var.push_back('\0');
	
	for (std::vector<std::string>::iterator it = storage.begin(); it != storage.end(); it++)
	{
		
	}

}