#include "Level.h"
#include "Application.h"
int Level::MAX_SCORE = 20;

Level::Level(std::string level2load, std::string avatar2load)
{
	FileReading fr;

	fr.loadFile("Levels//" + level2load);
	
	fr.loadVariables(&theball, ("Image//Avatars//" + avatar2load).c_str());
	Allassets.push_back(theball);

	fr.loadVariables(tools);

	fr.loadVariables(&Allassets);
	std::string orbit = ("Image//Particles//" + avatar2load);

	//Init Score Variables
	HighScore = 0;
	Score = 0;
	Mode = 0;
	collide = false;

	pm_Particles = new ParticleManager("Image//trail.tga", "Image//trail.tga", "Image//trail.tga", "Image//trail.tga", orbit.c_str(), "Image//trail.tga");
	
	std::string temp = fr.GetVariable("Levels//" + level2load, "max_score");
	if (temp == "")
		MAX_SCORE = 25;
	else
		MAX_SCORE = stoi(temp);
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
	bool collideWith = true;
	for (int i = 0; i < Allassets.size(); ++i)
	{
		if (!onlyUpdateGraphic)
		{
			Allassets[i]->update(dt);

			if (Allassets[i] != theball)
			{
				if (theball->checkColision(Allassets[i]))
				{
					if (Allassets[i]->GetApplyEffect() == false)
					{
						if (dynamic_cast<Cannon*>(Allassets[i]))
						{
							this->Score += 3;
							pm_Particles->SpawnParticles(ParticleManager::PARTICLE_CANNON, *Allassets[i]->getPointerPos(), Vector2(30, 30), 6, 50, 0.15f, 50);
							Allassets[i]->SetApplyEffect(true);
						}
						else if (dynamic_cast<Slow*>(Allassets[i]) || dynamic_cast<Boost*>(Allassets[i]))
						{
							this->Score += 2;
							Vector2 *temp = theball->getPointerPos();
							pm_Particles->SpawnParticles(ParticleManager::PARTICLE_SLOW, *temp, Vector2(20, 20), 4, 10, 0.2f, 9);
							Allassets[i]->SetApplyEffect(true);
						}
						else if (dynamic_cast<Wall*>(Allassets[i]))
						{
							this->Score += 1;
							Vector2 *temp = theball->getPointerPos();
							pm_Particles->SpawnParticles(ParticleManager::PARTICLE_WALL, *temp, Vector2(20, 20), 1, 10, 1, 3);
							Allassets[i]->SetApplyEffect(true);
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
				else
					Allassets[i]->SetApplyEffect(false);
			}
		}
		if (dynamic_cast<Exit*>(Allassets[i]))
		{
			dynamic_cast<Exit*>(Allassets[i])->updateGraphics(dt);
		}
	}

	pm_Particles->Update(dt);
	UpdateMode();
	return 1;

}

void Level::render(CSceneManager2D* sceneManager2D)
{
	for (int i = 0; i < Allassets.size(); ++i)
	{
		Allassets[i]->render(sceneManager2D);
	}
	pm_Particles->Render(sceneManager2D);
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
	int eachbar = MAX_SCORE / 5;

	prevMode = Mode;
	if (Score >= eachbar && Score < eachbar*2)
		Mode = 1;
	else if (Score >= eachbar * 2 && Score < eachbar * 3)
		Mode = 2;
	else if (Score >= eachbar * 3 && Score < eachbar * 4)
		Mode = 3;
	else if (Score >= eachbar * 4 && Score < MAX_SCORE)
		Mode = 4;
	else if (Score >= MAX_SCORE)
		Mode = 5;
	else
		Mode = 0;
	while (Mode > prevMode)
	{
		pm_Particles->SpawnParticles(ParticleManager::PARTICLE_PLAYER_ORBIT, *theball->getPointerPos(), Vector2(35, 35), 3, 20, 15.f, 1);
		prevMode++;
	}
}
