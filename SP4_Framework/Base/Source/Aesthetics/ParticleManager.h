#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "Particles.h"
#include <vector>

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	void SpawnParticles(char*, Vector2, Vector2[2], float[2], float[2], float[2], int, int);
	void Update(float dt);
	void Render(CSceneManager2D*);
private:
	std::vector<Particles*> p_Particles;
	bool disableParticles;
};

#endif