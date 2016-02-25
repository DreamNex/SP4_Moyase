#include "Level.h"

Level::Level(std::string level2load, std::string avatar2load)
{
	FileReading fr;

	fr.loadFile("Levels//" + level2load);
	
	fr.loadVariables(&theball, ("Image//Avatars//" + avatar2load).c_str());
	Allassets.push_back(theball);

	fr.loadVariables(tools);

	fr.loadVariables(&Allassets);
}

Level::~Level()
{
	for (int i = 0; i < Allassets.size(); ++i)
	{
		delete Allassets[i];
	}
}

void Level::update(double dt)
{
	for (int i = 0; i < Allassets.size(); ++i)
	{
		Allassets[i]->update(dt);

		if (Allassets[i] != theball)
		{
			if (theball->checkColision(Allassets[i]));
			{
			}
		}
	}
}

void Level::render(CSceneManager2D* sceneManager2D)
{
	for (int i = 0; i < Allassets.size(); ++i)
	{
		Allassets[i]->render(sceneManager2D);
	}
}

void Level::addTool(Tools* Tool)
{
	if (Tool)
	{
		Allassets.push_back(Tool);
	}
}