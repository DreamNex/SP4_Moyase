#ifndef LEVEL_H
#define LEVEL_H

#include "FileReading.h"
#include "Scenes\SceneManager2D.h"
#include "GameObjects\Cannon.h"
#include "GameObjects\Boost.h"
#include "GameObjects\Slow.h"

class Level
{
public:
	Level(std::string level2load, std::string avatar2load);
	~Level();
	
	int update(double dt);
	void render(CSceneManager2D* sceneManager2D);
	
	Balls* getBall() { return theball; }

	int* getToolsArray() { return tools; }

	std::vector<GameObject*>& getGameObjects() { return Allassets; }
	void addTool(Tools* Tool);

private:
	Balls* theball;
	int tools[3];
	std::vector<GameObject*> Allassets;
};

#endif