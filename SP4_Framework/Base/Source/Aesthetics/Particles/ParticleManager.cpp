#include "ParticleManager.h"
#include "GL\glew.h"
#include "../Base/Source/LoadTGA.h"
#include <stdlib.h>
#include "../Base/Source/Aesthetics/VectorPaths/Magnet.h"
#include "../Base/Source/Aesthetics/VectorPaths/Orbit.h"
#include "../Base/Source/Aesthetics/VectorPaths/Wave.h"


ParticleManager::ParticleManager(char *wall, char *cannon, char *boost, char *slow, const char *orbit, char * trail)
{
	mesh[PARTICLE_WALL] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	mesh[PARTICLE_WALL]->textureID = LoadTGA(wall);

	mesh[PARTICLE_CANNON] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	mesh[PARTICLE_CANNON]->textureID = LoadTGA(cannon);

	mesh[PARTICLE_BOOST] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	mesh[PARTICLE_BOOST]->textureID = LoadTGA(boost);

	mesh[PARTICLE_SLOW] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	mesh[PARTICLE_SLOW]->textureID = LoadTGA(slow);

	mesh[PARTICLE_PLAYER_ORBIT] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	mesh[PARTICLE_PLAYER_ORBIT]->textureID = LoadTGA(orbit);

	mesh[PARTICLE_PLAYER_TRAIL] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	mesh[PARTICLE_PLAYER_TRAIL]->textureID = LoadTGA(trail);

	srand(time(NULL));
}
ParticleManager::~ParticleManager()
{
}

float RandomFloat(float min, float max)
{
	return (min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max - min)));
}

void ParticleManager::Clear()
{
	p_Particles.clear();
}

void ParticleManager::SpawnParticles(PARTICLE_TYPE p_Type, Vector2& end, Vector2 size, float speed, float dist, float life, int amount)
{
	Vector2 up(0, 1);
	VectorPathing* vPath;
	if (p_Type == PARTICLE_PLAYER_ORBIT)
		vPath = new Orbit(1, 1);
	else if (p_Type == PARTICLE_CANNON)
		vPath = new Magnet(false);
	else
		vPath = new Magnet(true);

	for (unsigned int i = 0; i < amount; ++i)
	{
		float p_angle = RandomFloat(1, 359);
		Vector2 start = up;
		start.rotateVector(-p_angle);
		start = end + (start * dist);
		p_Particles.push_back(new Particles(vPath, start, end, size, speed, mesh[p_Type], new Timer(life)));
	}
}

void ParticleManager::SpawnParticles(PARTICLE_TYPE p_Type, Vector2& end, Vector2 sizeMin, Vector2 sizeMax, float speed, float distMin, float distMax, float lifeMin, float lifeMax, int amount)
{
	Vector2 up(0, 1);
	VectorPathing* vPath;
	if (p_Type == PARTICLE_PLAYER_ORBIT)
		vPath = new Orbit(1, 1);
	else if (p_Type == PARTICLE_CANNON || p_Type == PARTICLE_PLAYER_TRAIL)
		vPath = new Magnet(false);
	else
		vPath = new Magnet(true);

	for (unsigned int i = 0; i < amount; ++i)
	{
		float temp = RandomFloat(sizeMin.x, sizeMax.x);
		Vector2 size(temp, temp);
		float life = RandomFloat(lifeMin, lifeMax);
		float dist = RandomFloat(distMin, distMax);
		float p_angle = RandomFloat(1, 359);
		Vector2 start = up;
		start.rotateVector(-p_angle);
		start = end + (start * dist);
		p_Particles.push_back(new Particles(vPath, start, end, size, speed, mesh[p_Type], new Timer(life)));
	}
}

void ParticleManager::Update(float dt)
{
	for (unsigned int i = 0; i < p_Particles.size(); ++i)
	{
		if (p_Particles[i]->Update(dt))
		{ 
			if (p_Particles[i]->GetLife()->GetLoop())
			{ 
				p_Particles[i]->GetLife()->Start();
				continue;
			}
			p_Particles.erase(p_Particles.begin() + i);
		}
	}
}

void ParticleManager::Render(CSceneManager2D *sm)
{
	for (unsigned int i = 0; i < p_Particles.size(); ++i)
	{
		p_Particles[i]->Render(sm);
	}
}
