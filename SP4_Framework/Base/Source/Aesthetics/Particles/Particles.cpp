#include "Particles.h"
#include "GL\glew.h"
#include "../Base/Source/LoadTGA.h"

/*************************************************************************************************************
	CONSTRUCTOR(S) && DESTRUCTOR
*************************************************************************************************************/
Particles::Particles(int vPath, Vector2 start, Vector2& end, Vector2 size, float speed, Mesh* mesh, Timer* life)
{
	this->start = start;
	this->end = &end;
	this->size = size;
	this->speed = speed;
	this->life = life;
	this->particlePath = new VectorPathing(vPath);

	this->particleMesh = mesh;
}
Particles::Particles()
	: life(new Timer(5.0f))
	, size(Vector2(1, 1))
	, start(Vector2(1, 1))
	, end(NULL)
	, speed(1)
	, particlePath(new VectorPathing(1))
{
}
Particles::~Particles()
{
	delete particlePath;
	delete life;
	delete particleMesh;
}


/*************************************************************************************************************
	ACCESOR(S)
*************************************************************************************************************/
Timer* Particles::GetLife()
{
	return this->life;
}
Mesh* Particles::GetMesh()
{
	return this->particleMesh;
}
Vector2 Particles::GetSize()
{
	return this->size;
}
Vector2 Particles::GetStart()
{
	return this->start;
}
Vector2 Particles::GetEnd()
{
	return *(this->end);
}
float Particles::GetSpeed()
{
	return this->speed;
}
VectorPathing* Particles::GetParticlePath()
{
	return this->particlePath;
}


/*************************************************************************************************************
	MUTATOR(S)
*************************************************************************************************************/
void Particles::SetLife(Timer* life)
{
	this->life = life;
}
void Particles::SetMesh(Mesh* mesh)
{
	this->particleMesh = mesh;
}
void Particles::SetSize(Vector2 s)
{
	this->size = s;
}
void Particles::SetStart(Vector2 start)
{
	this->start = start;
}
void Particles::SetEnd(Vector2& end)
{
	this->end = &end;
}
void Particles::SetSpeed(float sp)
{
	this->speed = sp;
}

bool Particles::Update(float dt)
{
	if (prevEnd != 0)
	{
		if (prevEnd != *end)
		{
			Vector2 offset = *end - prevEnd;
			start = start + offset;
		}
	}
	Vector2 path = particlePath->GetPath(start, *end) * speed;
	if (life->Update(dt) || path.IsZero())
		return true;
	start = start + path;
	prevEnd = *end;
	return false;
}
void Particles::Render(CSceneManager2D* scene)
{
	scene->RenderMeshIn2D(particleMesh, false, size.x, size.y, start.x, start.y);
}