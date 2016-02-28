#include "ParticleManager.h"
#include "GL\glew.h"
#include "../LoadTGA.h"
#include "VectorPathing.h"
#include <stdlib.h>

float RandomFloat(float min, float max)
{
	return (min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max - min)));
}

void ParticleManager::SpawnParticles(char* Mesh, Vector2 origin, Vector2 size[2], float angle[2], float speed[2], float dist[2], float life[2], int type, int amount)
{
	srand(time(NULL));
	Vector2 up(0, 1);
	for (unsigned int i = 0; i < amount; ++i)
	{
		Vector2 p_size(RandomFloat(size[0].x, size[1].x), RandomFloat(size[0].y, size[1].y));
		float p_speed = RandomFloat(speed[0], speed[1]);
		float p_dist = RandomFloat(dist[0], dist[1]);
		float p_angle = RandomFloat(angle[0], angle[1]);
		float p_life = RandomFloat(life[0], life[1]);
		Vector2 start;
		start.rotateVector(-p_angle);
		p_Particles.push_back(new Particles(type, start, origin, p_size, p_speed, Mesh, new Timer(p_life)));
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
