#include "Level.h"

Level::Level(std::string level2load, std::string avatar2load)
{
	FileReading fr;

	fr.loadFile("Levels//" + level2load);
	
	fr.loadVariables(&theball, ("Image//Avatars//" + avatar2load).c_str());
	Allassets.push_back(theball);

	fr.loadVariables(tools);

	fr.loadVariables(&Allassets);

	//Init Score Variables
	HighScore = 0;
	Score = 0;
	Mode = 0;
}

Level::~Level()
{
	for (int i = 0; i < Allassets.size(); ++i)
	{
		delete Allassets[i];
	}
}

int Level::update(double dt, bool onlyUpdateGraphic)
{
	for (int i = 0; i < Allassets.size(); ++i)
	{
		if (!onlyUpdateGraphic)
		{
			Allassets[i]->update(dt);

			if (Allassets[i] != theball)
			{
				if (theball->checkColision(Allassets[i]))
				{
					if (dynamic_cast<Cannon*>(Allassets[i]))
					{
						this->Score += 3;
					}
					else if (dynamic_cast<Slow*>(Allassets[i]) || dynamic_cast<Boost*>(Allassets[i]))
					{
						this->Score += 2;
					}
					else if (dynamic_cast<Wall*>(Allassets[i]))
					{
						this->Score += 1;
					}
					else if (dynamic_cast<Exit*>(Allassets[i]))
					{
						return 3;
					}
					else if (dynamic_cast<Spikes*>(Allassets[i]))
					{
						return 0;
					}
				}
			}
		}
		if (dynamic_cast<Exit*>(Allassets[i]))
		{
			dynamic_cast<Exit*>(Allassets[i])->updateGraphics(dt);
		}
	}
	UpdateMode();
	return 1;
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

//SCORE SYSTEM
int Level::GetScore(void)const
{
	return this->Score;
}
void Level::SetScore(int score)
{
	this->Score = score;
}

int Level::GetMode(void)const //Score Level depends on your Score, eg. Score of 5 = Mode 1
{
	return this->Mode;
}
void Level::UpdateMode()
{
	if (Score >= 5 && Score < 10)
		Mode = 1;
	else if (Score >= 10 && Score < 15)
		Mode = 2;
	else if (Score >= 15 && Score < 20)
		Mode = 3;
	else if (Score >= MAX_SCORE)
		Mode = 4;
	else
		Mode = 0;
}
