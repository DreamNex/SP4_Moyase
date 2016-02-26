#include "Particles.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Particles::Particles(int vPath, Vector2 start, Vector2 end, Vector2 size, float speed, char* mesh, Timer* life)
{
	this->pos = pos;
	this->size = size;
	this->speed = speed;
	this->life = life;
	this->particlePath = new VectorPathing(vPath, start, end);

	this->particleMesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, size.x, size.y);
	this->particleMesh->textureID = LoadTGA(mesh);
}
Particles::Particles()
	: life(new Timer(5.0f))
	, size(Vector2(1, 1))
	, pos(Vector2(1, 1))
	, speed(1)
	, particlePath(new VectorPathing(1, Vector2(0, 0), Vector2(0, 0)))
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
Vector2 Particles::GetPos()
{
	return this->pos;
}
float Particles::GetSpeed()
{
	return this->speed;
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
void Particles::SetPos(Vector2 p)
{
	this->pos = p;
}
void Particles::SetSpeed(float sp)
{
	this->speed = sp;
}

bool Particles::Update(float dt)
{
	if (life->Update(dt))
		return true;
	pos = pos + (particlePath->GetPath() * speed);
	return false;
}
void Particles::Render(CSceneManager2D* scene)
{
	scene->RenderMeshIn2D(particleMesh, false, size.x, size.y, pos.x, pos.y);
}