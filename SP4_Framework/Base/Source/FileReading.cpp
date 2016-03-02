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
void FileReading::loadFile(std::string filename)
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
	int i = 0;
	while (std::getline(splitter, token, ','))
	{
		tool[i] = atoi(token.c_str());
		i++;
	}
}
void FileReading::loadVariables(Balls** Ball, const char* avatarToload)
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
			x = std::stof(token.c_str());
			
			//Split third part, pos.y
			std::getline(splitter, token, ',');
			y = std::stof(token.c_str());

			//Split fourth part, diameter
			std::getline(splitter, token, ',');
			diameter = (float)atoi(token.c_str());

			(*Ball) = new Balls(Vector2(x, y), diameter, avatarToload);
			break;
		}
	}
}
void FileReading::loadVariables(std::vector<GameObject*>* GameObjects)
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
			x = std::stof(token.c_str());

			//Split third part, pos.y
			std::getline(splitter, token, ',');
			y = std::stof(token.c_str());

			//Split fourth part, scaleX
			std::getline(splitter, token, ',');
			scaleX = std::stof(token.c_str());

			//Split fifth part, scale y
			std::getline(splitter, token, ',');
			scaleY = std::stof(token.c_str());

			(*GameObjects).push_back(new Wall(Vector2(x, y), scaleX, scaleY));
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
			x = std::stof(token.c_str());

			//Split third part, pos.y
			std::getline(splitter, token, ',');
			y = std::stof(token.c_str());

			//Split fourth part, scaleX
			std::getline(splitter, token, ',');
			scaleX = std::stof(token.c_str());

			//Split fifth part, scale y
			std::getline(splitter, token, ',');
			scaleY = std::stof(token.c_str());

			(*GameObjects).push_back(new Spikes(Vector2(x, y), scaleX, scaleY));
		}
		else if (it->find("exit") != std::string::npos)
		{
			float x, y, scaleX, scaleY;
			std::stringstream splitter(it->c_str());

			//split first part (Type of gameobject)
			std::getline(splitter, token, ',');
			std::string temp = token;

			//Split second part, pos.x
			std::getline(splitter, token, ',');
			x = std::stof(token.c_str());

			//Split third part, pos.y
			std::getline(splitter, token, ',');
			y = std::stof(token.c_str());

			//Split fourth part, scaleX
			std::getline(splitter, token, ',');
			scaleX = std::stof(token.c_str());

			//Split fifth part, scale y
			std::getline(splitter, token, ',');
			scaleY = std::stof(token.c_str());

			(*GameObjects).push_back(new Exito(Vector2(x, y), scaleX, scaleY));
		}
	}
}
//Clears the vectors' of strings containing all ur lines frm the test file
void FileReading::ClearStorage()
{
	storage.clear();
}

void FileReading::changeUnlock(std::string filename)
{
	std::ifstream ifile;
	std::string Checker = "false";
	std::string line;
	storage.clear();

	ifile.open(filename);
	if (ifile.is_open())
	{
		while (std::getline(ifile, line))
		{
			std::istringstream ss(line);
			storage2.push_back(line);
		}
	}

	ifile.close();

	if (storage2.at(0) == Checker)
	{
		storage2.at(0) = "true";
	}

	std::ofstream ofile(filename);
	for (auto const& line : storage2)
	{
		ofile << line << '\n';
	}
}

float FileReading::GetFloatVal(std::string filename, std::string searchFor)
{
	std::ifstream ifile;
	std::string line;
	float returnVal;
	storage3.clear();

	ifile.open(filename);
	if (ifile.is_open())
	{
		while (std::getline(ifile, line))
		{
			std::istringstream ss(line);
			storage3.push_back(line);
		}
	}

	for (std::vector<std::string>::iterator it = storage3.begin(); it < storage3.end(); it++)
	{
		if (it->find(searchFor) != std::string::npos)
		{
			
			std::stringstream splitter(it->c_str());
			std::string token;

			std::getline(splitter, token, ' ');
			std::string temp = token;


			std::getline(splitter, token, ' ');
			temp = token;

			std::getline(splitter, token, ' ');
			returnVal = std::stof(token.c_str());

		}

	}

	return returnVal;
}

void FileReading::SetFloatVal(std::string filename, std::string searchFor, float value)
{
	std::ifstream ifile;
	std::string line;
	
	storage3.clear();
	
	ifile.open(filename);
	if (ifile.is_open())
	{
		while (std::getline(ifile, line))
		{
			std::istringstream ss(line);
			storage3.push_back(line);
		}
	}

	ifile.close();

	for (int i = 0; i < storage3.size(); i++)
	{
		if (storage3[i].find(searchFor) != std::string::npos)
		{
			std::ostringstream buff;
			buff << value;
			std::string line2 = searchFor + " = " + buff.str();
			storage3[i] = line2;
		}
	}

	std::ofstream ofile(filename);
	for (auto const& line : storage3)
	{
		ofile << line << '\n';
	}

}

std::vector<std::string>  FileReading::SearchFolder(std::string directory, std::string fileExtemtion)
{
	std::vector<std::string> storageFN;
	std::string searchPattern = fileExtemtion;
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

std::string FileReading::GetVariable(std::string filename, std::string searchFor)
{
	std::ifstream ifile;
	std::string line;
	std::string temp;
	storage3.clear();

	ifile.open(filename);
	if (ifile.is_open())
	{
		while (std::getline(ifile, line))
		{
			std::istringstream ss(line);
			storage3.push_back(line);
		}
	}

	for (std::vector<std::string>::iterator it = storage3.begin(); it < storage3.end(); it++)
	{
		if (it->find(searchFor) != std::string::npos)
		{

			std::stringstream splitter(it->c_str());
			std::string token;

			std::getline(splitter, token, ' ');
			temp = token;


			std::getline(splitter, token, ' ');
			temp = token;

			std::getline(splitter, token, ' ');
			temp = token;

		}

	}

	return temp;
}