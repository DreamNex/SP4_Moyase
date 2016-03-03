#include "Rebound.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Rebound::Rebound(Vector2 pos, float radius)
: Enviroment(pos)
{
	this->rigidBody = new RigidBody(new Circle(this->pos, radius), new PhysicsComponent(this->pos, 1, false), false);
	
	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0, 0, 0), 0, 0, 1, 1);
	this->mesh->textureID = LoadTGA("Image//rebound.tga");

	WaveMesh = MeshBuilder::Generate2DMesh("Mesh", Color(0, 0, 0), 0, 0, 1, 1);
	WaveMesh->textureID = LoadTGA("Image//rebound_wave.tga");

	waveActive = false;;
	WaveScale = 1;

	trans = 0;
}

Rebound::~Rebound()
{
	onDestory();
}

void Rebound::updateGraphics(double dt)
{
	this->rigidBody->Update((float)dt);

	if (waveActive)
	{
		if (WaveScale > this->rigidBody->GetScale(0))
		{
			trans += dt * 250;
			if (trans > 100)
			{
				trans = 0;
				WaveScale = 1;
				waveActive = false;
			}
		}
		else
			WaveScale += dt * this->rigidBody->GetScale(0)*2;
	}
}

void Rebound::render(CSceneManager2D* SceneManager2D)
{
	if (waveActive)
		SceneManager2D->Render2DMeshTrams(WaveMesh, (int)trans, WaveScale, WaveScale, this->pos.x - WaveScale*0.5f, this->pos.y - WaveScale*0.5f);
	
	SceneManager2D->Render2DMesh(this->mesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - this->rigidBody->GetScale(0)*0.5f, this->pos.y - this->rigidBody->GetScale(1)*0.5f);
}