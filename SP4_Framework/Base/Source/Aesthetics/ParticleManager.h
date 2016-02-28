#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "Particles.h"
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
	};
	ParticleManager(char *wall, char *cannon, char *boost, char *slow, char *orbit, char * trail);
	~ParticleManager();

	void SpawnParticles(char*, Vector2, Vector2[2], float[2], float[2], float[2], float[2], int, int);
	void Update(float dt);
	void Render(CSceneManager2D*);
private:
	Mesh* mesh[6];
	std::vector<Particles*> p_Particles;
	bool disableParticles;
};

#endif