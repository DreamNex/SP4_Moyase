#ifndef FILE_READING_H
#define FILE_READING_H

#include <vector>
#include <fstream>
#include <string>
#include <cstring>

class FileReading
{
public:
	FileReading();
	~FileReading();

	void Init();
	
	//It will check the type of gameobject and get variables[FORMATT: pos.x, pos.y, scale x, scale y ]
	std::vector<std::string> loadVariables(std::vector<std::string> &storage, std::string filename);
	void saveVariables(std::string filename);
	
private:
	
	

};
#endif