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
	std::vector<std::string> storage;
	//It will check the type of gameobject and get variables[FORMATT: pos.x, pos.y, scale x, scale y ]
	void loadVariables(std::string filename, bool unlock, int tool[3]);

	
	
private:
	
	

};
#endif