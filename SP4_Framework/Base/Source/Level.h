#ifndef LEVEL_H
#define LEVEL_H

#include "FileReading.h"

class Level
{
	Level();
	Level(bool unlock, int tools[3]);
	~Level();

public:
	int tools[3];
	bool unlock;
	//Enviroment
	//Stores the things from the different files0
	//std::vector<std::string> Enviroment;
	//std::vector<GameObject> Spikes;
	//std::vector<GameObject> wall;

	std::vector<GameObject*> assets;
	Balls *player;
	
};

#endif