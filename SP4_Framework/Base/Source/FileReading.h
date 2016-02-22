#ifndef FILE_READING_H
#define FILE_READING_H

#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <Windows.h>

#include "GameObjects\Balls.h"
#include "GameObjects\Spikes.h"
#include "GameObjects\Wall.h"

class FileReading
{
public:
	FileReading();
	~FileReading();
	
	//It will check the type of gameobject and get variables[FORMATT: pos.x, pos.y, scale x, scale y ]
	void loadVariables(std::string filename, bool &unlock, int (&tool)[3]);
	void loadVariables(Balls** Ball);
	void loadVariables(std::vector<Enviroment*>* EnviromentObjs);
	

	//Folder Searching
	void SearchFolder(std::string directory);
	//Clear vector storage
	void ClearStorage();

private:
	
	std::vector<std::string> storage;

};
#endif