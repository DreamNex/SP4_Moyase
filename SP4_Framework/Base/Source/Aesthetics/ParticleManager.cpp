#include "ParticleManager.h"
#include "GL\glew.h"
#include "../LoadTGA.h"
#include "VectorPathing.h"

void ParticleManager::SpawnParticles(char* Mesh, Vector2 origin, Vector2 size[2], float angle[2], float speed[2], float dist[2], int type, int amount)
{
	for (unsigned int i = 0; i < amount; ++i)
	{
	}
}

void ParticleManager::Update(float dt)
{
	for (unsigned int i = 0; i < p_Particles.size(); ++i)
	{
		if (p_Particles[i]->Update(dt))
			p_Particles.erase(p_Particles.begin() + i);
	}
}

void ParticleManager::Render(CSceneManager2D *sm)
{
	for (unsigned int i = 0; i < p_Particles.size(); ++i)
	{
		p_Particles[i]->Render(sm);
	}
}
