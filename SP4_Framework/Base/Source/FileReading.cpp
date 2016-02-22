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
void FileReading::loadVariables(std::string filename, bool &unlock, int (&tool)[3])
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
			tool[i] = atoi(token.c_str());
		}
	}
}

void FileReading::loadVariables(Balls** Ball)
{
	std::string token;
	for (std::vector<std::string>::iterator it = storage.begin(); it < storage.end(); it++)
	{
		if (it->find("ball") != std::string::npos)
		{
			float x, y, diameter;
			std::stringstream splitter(it->c_str());
			
			//split first part (Type of gameobject)
			std::getline(splitter, token, ',');
			std::string temp = token;

			//Split second part, pos.x
			std::getline(splitter, token, ',');
			x = (float)atoi(token.c_str());
			
			//Split third part, pos.y
			std::getline(splitter, token, ',');
			y = (float)atoi(token.c_str());

			//Split fourth part, diameter
			std::getline(splitter, token, ',');
			diameter = (float)atoi(token.c_str());

			(*Ball) = new Balls(Vector2(x, y), diameter,"Image//Tits//Avatar_Censored.tga");
			break;
		}
	}
}

void FileReading::loadVariables(std::vector<Enviroment*>* EnviromentObjs)
{
	std::string token;
	for (std::vector<std::string>::iterator it = storage.begin(); it < storage.end(); it++)
	{
		if (it->find("wall") != std::string::npos)
		{
			float x, y, scaleX, scaleY;
			std::stringstream splitter(it->c_str());

			//split first part (Type of gameobject)
			std::getline(splitter, token, ',');
			std::string temp = token;

			//Split second part, pos.x
			std::getline(splitter, token, ',');
			x = (float)atoi(token.c_str());

			//Split third part, pos.y
			std::getline(splitter, token, ',');
			y = (float)atoi(token.c_str());

			//Split fourth part, scaleX
			std::getline(splitter, token, ',');
			scaleX = (float)atoi(token.c_str());

			//Split fifth part, scale y
			std::getline(splitter, token, ',');
			scaleY = (float)atoi(token.c_str());

			(*EnviromentObjs).push_back(new Wall(Vector2(x, y), scaleX, scaleY));
		}

		if (it->find("spike") != std::string::npos)
		{
			float x, y, scaleX, scaleY;
			std::stringstream splitter(it->c_str());

			//split first part (Type of gameobject)
			std::getline(splitter, token, ',');
			std::string temp = token;

			//Split second part, pos.x
			std::getline(splitter, token, ',');
			x = (float)atoi(token.c_str());

			//Split third part, pos.y
			std::getline(splitter, token, ',');
			y = (float)atoi(token.c_str());

			//Split fourth part, scaleX
			std::getline(splitter, token, ',');
			scaleX = (float)atoi(token.c_str());

			//Split fifth part, scale y
			std::getline(splitter, token, ',');
			scaleY = (float)atoi(token.c_str());

			(*EnviromentObjs).push_back(new Spikes(Vector2(x, y), scaleX, scaleY));
		}
	}
}

//Clears the vectors' of strings containing all ur lines frm the test file
void FileReading::ClearStorage()
{
	storage.clear();
}