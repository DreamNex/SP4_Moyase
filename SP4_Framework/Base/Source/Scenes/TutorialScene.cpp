#include "TutorialScene.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include <sstream>

CTutorialScene::CTutorialScene()
{
}

CTutorialScene::CTutorialScene(int m_window_width, int m_window_height)
:
CSceneManager2D(m_window_width, m_window_height)
{
}

CTutorialScene::~CTutorialScene()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
}

void CTutorialScene::Init()
{
	CSceneManager2D::Init();

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	gameObjects.push_back(new Balls(Vector2(700, 700), 50, "Image//Tits//Avatar_Censored.tga"));
	gameObjects.push_back(new Wall(Vector2(1280 /2, 400), 1280 - 100, 100));
	gameObjects.push_back(new Spikes(Vector2(1280 / 2, 400), Vector2(700, 700), 1280, 100));
}

void CTutorialScene::Update(double dt)
{
	std::cout << gameObjects[0]->getPos().x << ", " << gameObjects[0]->getPos().y << std::endl;
	if (Application::IsKeyPressed('W'))
	{
		std::cout << "W: ";
		gameObjects[0]->getRigidBody()->GetPhysicsCompt()->ApplyForce(Vector2(0, 0.00002f));
	}
	
	gameObjects[0]->checkColision(gameObjects[1]);
	//gameObjects[0]->checkColision(gameObjects[2]);
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update(dt);
	}
}

void CTutorialScene::Render()
{
	CSceneManager2D::Render();
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render(this);
	}
}

void CTutorialScene::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}