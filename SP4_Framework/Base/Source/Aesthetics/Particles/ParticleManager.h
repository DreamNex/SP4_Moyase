#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "Particles.h"
#include "../Base/Source/Scenes/SceneManager2D.h"
#include <vector>

class ParticleManager
{
public:
	enum PARTICLE_TYPE
	{
		PARTICLE_WALL,
		PARTICLE_CANNON,
		PARTICLE_BOOST,
		PARTICLE_SLOW,
		PARTICLE_PLAYER_ORBIT,
		PARTICLE_PLAYER_TRAIL,
		PARTICLE_SIZE,
	};
	ParticleManager(char *wall, char *cannon, char *boost, char *slow, const char *orbit, char * trail);
	ParticleManager();
	~ParticleManager();

	void Clear();
	void SpawnParticles(PARTICLE_TYPE p_Type, Vector2& end, Vector2 size, float speed, float dist, float life, int amount);
	void SpawnParticles(PARTICLE_TYPE p_Type, Vector2& end, Vector2 sizeMin, Vector2 sizeMax, float speed, float distMin, float distMax, float lifeMin, float lifeMax, int amount);
	void Update(float dt);
	void Render(CSceneManager2D*);
private:
	Mesh* mesh[PARTICLE_SIZE];
	std::vector<Particles*> p_Particles;
};

#endif