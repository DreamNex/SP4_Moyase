#ifndef LEVEL_H
#define LEVEL_H

#include "FileReading.h"
#include "Scenes\SceneManager2D.h"
#include "GameObjects\Cannon.h"
#include "GameObjects\Boost.h"
#include "GameObjects\Slow.h"
#include "Aesthetics\Particles\ParticleManager.h"

class Level
{
public:
	Level(std::string level2load, std::string avatar2load);
	~Level();
	
	int update(double dt, bool onlyUpdateGraphic = false, bool increaseScore = true);
	void render(CSceneManager2D* sceneManager2D);
	
	Balls* getBall() { return theball; }
	int* getToolsArray() { return tools; }

	ParticleManager* GetParticleManager(){ return this->pm_Particles; }

	std::vector<GameObject*>& getGameObjects() { return Allassets; }
	void addTool(Tools* Tool);

	int GetScore(void)const;
	void SetScore(int);

	static int GetMaxScore() { return MAX_SCORE; }

	int GetMode(void)const; //Score Level depends on your Score, eg. Score of 5 = Mode 1
	void UpdateMode();
private:
	Balls* theball;
	bool collide;
	int tools[3];
	std::vector<GameObject*> Allassets;
	std::vector<GameObject*> currentCollision;

	//Level's Score(Depends on the Amount Of Collision Made)
	static int MAX_SCORE;
	int HighScore;
	int Score;
	int Mode; //Depends on Score
	int prevMode;

	//Aesthetics
	ParticleManager* pm_Particles;
};

#endif