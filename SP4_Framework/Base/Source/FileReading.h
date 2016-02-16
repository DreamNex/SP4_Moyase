#ifndef FILE_READING_H
#define FILE_READING_H

#include <vector>
#include <fstream>
#include <string>

class FileReading
{
	FileReading();
	~FileReading();

	void Init();
	
	void loadVariables(std::vector<float> storage, std::string filename);
	void saveVariables(std::string filename);


};
#endif