#include <iostream>
#include <sstream>
#include "FileReading.h"


FileReading::FileReading(std::string filename)
{
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
}

FileReading::~FileReading()
{

}

// Be abl to open any text file you want and store it into a vector
void FileReading::loadVariables(bool &unlock)
{	
	if (storage.at(0) == "true")
	{
		unlock = true;
	}
	else if (storage.at(0) == "false")
	{
		unlock = false;
	}

}
void FileReading::loadVariables(int(&tool)[3])
{
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
		else if (it->find("spike") != std::string::npos)
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

std::vector<std::string>  FileReading::SearchFolder(std::string directory)
{
	std::vector<std::string> storageFN;
	std::string searchPattern = "*.txt";
	std::string fullPath = directory + searchPattern;
	
	char ch[260];
	char DefChar = ' ';

	std::wstring ptemp = std::wstring(directory.begin(), directory.end());
	std::wstring stemp = std::wstring(fullPath.begin(), fullPath.end());
	
	const wchar_t* ptemp2 = ptemp.c_str();

	LPCWSTR fp = stemp.c_str();

	WIN32_FIND_DATA findData;
	HANDLE handleFind;
	
	handleFind = FindFirstFile(fp, &findData);

	if (handleFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error searching directory \n";
	}

	do
	{
		WideCharToMultiByte(CP_ACP, 0, findData.cFileName, -1, ch, 260, &DefChar, NULL);

		std::string fileName(ch);
		std::string filePath = directory + fileName;
		std::ifstream in(filePath.c_str());
		if (in)
		{
			//do things with file here
			storageFN.push_back(fileName);

		}

		else
		{
			std::cout << "Cannot open file " << fileName << std::endl;
		}
	}

	while (FindNextFile(handleFind, &findData) > 0);
	
	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		std::cout << "Something went wrong during searching \n" << std::endl;
	}
	return storageFN;
}