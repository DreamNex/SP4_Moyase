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
#include "GameObjects\Exit.h"
#include"GameObjects\Rebound.h"

class FileReading
{
public:
	FileReading();
	~FileReading();
	
	void loadFile(std::string filename);
	void loadVariables(bool &unlock);
	void loadVariables(int(&tool)[3]);
	//It will check the type of gameobject and get variables[FORMATT: pos.x, pos.y, scale x, scale y ]
	void loadVariables(Balls** Ball, const char* avatarToload);
	void loadVariables(std::vector<GameObject*>* GameObjects);
	
	// Get Volume
	float GetFloatVal(std::string filename, std::string searchFor);
	void SetFloatVal(std::string filename, std::string searchFor, float value);

	//Change the level bool to true
	void changeUnlock(std::string filename);
	
	//Folder Searching
	std::vector<std::string> SearchFolder(std::string directory, std::string fileExtention);
	
	//Clear vector storage
	void ClearStorage();

	//Get Variables
	std::string GetVariable(std::string filename, std::string searchFor);

private:
	
	std::vector<std::string> storage;  // to store the things from the text file;
	std::vector<std::string> storage2; // to replace the first line
	std::vector<std::string> storage3;
};
#endif