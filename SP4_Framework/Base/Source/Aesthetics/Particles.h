#ifndef PARTICLES_H
#define PARTICLES_H

#include "../MeshBuilder.h"
#include "../Scenes\SceneManager2D.h"
#include "../Timer/Timer.h"
#include "Vector2.h"
#include "VectorPathing.h"

class Particles
{
public:
	Particles(int vPath, Vector2 start, Vector2& end, Vector2 size, float speed, Mesh* mesh, Timer* life);
	Particles();
	~Particles();

	//ACCESSOR(S)
	Timer* GetLife();
	Mesh* GetMesh();
	Vector2 GetSize();
	Vector2 GetStart();
	Vector2 GetEnd();
	float GetSpeed();
	VectorPathing* GetParticlePath();

	//MUTATOR(S)
	void SetParticle(int vPath, Vector2 start, Vector2& end, Vector2 size, float speed, Mesh* mesh, Timer* life);
	void SetLife(Timer*);
	void SetMesh(Mesh*);
	void SetSize(Vector2);
	void SetStart(Vector2);
	void SetEnd(Vector2&);
	void SetSpeed(float);

	void Render(CSceneManager2D*);
	bool Update(float dt);
private:
	VectorPathing* particlePath;
	Timer* life;
	Mesh* particleMesh;
	Vector2 size; //Scale X, Scale Y
	Vector2 start;
	Vector2* end;
	Vector2 prevEnd;
	float speed;
};

#endif