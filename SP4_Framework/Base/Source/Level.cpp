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
	std::string orbit = ("Image//Particles//Orbit_" + avatar2load);

	//Init Score Variables
	HighScore = 0;
	Score = 0;
	Mode = 0;
	collide = false;

	pm_Particles = new ParticleManager("Image//Particles//WallParticle.tga", "Image//Particles//CannonParticle.tga",
										"Image//Particles//Boost.tga", "Image//Particles//Slow.tga",
										orbit.c_str(), "Image//Particles//Trail.tga");
	
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

int Level::update(double dt, bool onlyUpdateGraphic, bool increaseScores)
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
					if (Allassets[i]->GetApplyEffect() == false && increaseScores)
					{
						if (dynamic_cast<Cannon*>(Allassets[i]))
						{
							this->Score += 3;
							pm_Particles->SpawnParticles(ParticleManager::PARTICLE_CANNON, *Allassets[i]->getPointerPos(), Vector2(15, 15), 3, 1, 0.3f, 50);
							Allassets[i]->SetApplyEffect(true);
						}
						else if (dynamic_cast<Slow*>(Allassets[i]) || dynamic_cast<Boost*>(Allassets[i]))
						{
							this->Score += 2;
							Vector2 *temp = Allassets[i]->getPointerPos();
							if (dynamic_cast<Slow*>(Allassets[i]))
								pm_Particles->SpawnParticles(ParticleManager::PARTICLE_SLOW, *temp, Vector2(25, 25), 2.5, 80, 0.35f, 20);
							else
								pm_Particles->SpawnParticles(ParticleManager::PARTICLE_BOOST, *temp, Vector2(25, 25), 2.5, 80, 0.35f, 20);
							Allassets[i]->SetApplyEffect(true);
						}
						else if (dynamic_cast<Wall*>(Allassets[i]))
						{
							this->Score += 1;
							Vector2 *temp = new Vector2(theball->getPos().x, theball->getPos().y);
							pm_Particles->SpawnParticles(ParticleManager::PARTICLE_WALL, *temp, Vector2(20, 20), -2.5, 1, 0.5f, 3);
							Allassets[i]->SetApplyEffect(true);
						}
						else if (dynamic_cast<Exito*>(Allassets[i]))
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
		if (dynamic_cast<Enviroment*>(Allassets[i]))
		{
			if (dynamic_cast<Spikes*>(Allassets[i]))
			{
				dynamic_cast<Spikes*>(Allassets[i])->updateGraphics(dt);
			}
			else if (dynamic_cast<Rebound*>(Allassets[i]))
			{
				dynamic_cast<Rebound*>(Allassets[i])->updateGraphics(dt);
			}
			else if (dynamic_cast<Exito*>(Allassets[i]))
			{
				dynamic_cast<Exito*>(Allassets[i])->updateGraphics(dt);
			}
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
