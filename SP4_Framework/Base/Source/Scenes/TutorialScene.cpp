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

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("Game_bg", Color(1, 1, 1), 0, 0, 1, 1);
	meshList[GEO_BG]->textureID = LoadTGA("Image//g_bg.tga");

	meshList[GEO_TEST] = MeshBuilder::Generate2DMesh("Game_bg", Color(1, 1, 1), 0, 0, 1, 1);
	meshList[GEO_TEST]->textureID = LoadTGA("Image//Avatars//Avatar_Censored.tga");

	gameObjects.push_back(new Balls(Vector2(300, 700), 50, "Image//Avatars//Avatar_Censored.tga"));
	gameObjects.push_back(new Wall(Vector2(((float)m_window_width *0.5f), 100.f), (float)m_window_width - 100.f, 100.f));
	gameObjects.push_back(new Spikes(Vector2((float)m_window_width *0.5f, 100.f), (float)m_window_width, 100.f));
	gameObjects.push_back(new Wall(Vector2((float)m_window_width * 0.5f, (float)m_window_height * 0.5f), 100.f, (float)m_window_height - 100.f));

	gameObjects.push_back(new Cannon(Vector2(300.f, 350.f), 50.f, 50.f));
	gameObjects.push_back(new Boost(Vector2(300.f, 500.f), 50.f, 50.f));
	gameObjects.push_back(new Slow(Vector2(300.f, 700.f), 50.f, 50.f));

	cursor = new Cursor("Image//Avatars//Avatar_Censored.tga", "Image//Avatars//Avatar_5.tga","Image//Avatars//Avatar_5.tga", 1.5f, 20, 20);
	//m_GUI = new GUIManager(5, 5, 5);
	
	//ctrs = new Controls(m_GUI);
}

void CTutorialScene::Update(double dt)
{
	//Check which state
	//G_States = static_cast<GameStates>(ctrs->GetState());

	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	//mL_state = mR_state = false;
	bool m_state = false;

	std::cout << gameObjects[0]->getRigidBody()->GetPhysicsCompt()->GetVelocity().y << std::endl;
	std::cout << "~~" << std::endl;
	if (Application::IsKeyPressed('W'))
	{
		gameObjects[0]->getRigidBody()->GetPhysicsCompt()->Push(Vector2(0, 20.f));
	}
	if (Application::IsKeyPressed('S'))
	{
		gameObjects[0]->getRigidBody()->GetPhysicsCompt()->Push(Vector2(0, -1.f));
	}
	if (Application::IsKeyPressed('A'))
	{
		gameObjects[0]->getRigidBody()->GetPhysicsCompt()->Push(Vector2(-35.f, 0));
	}
	if (Application::IsKeyPressed('D'))
	{
		gameObjects[0]->getRigidBody()->GetPhysicsCompt()->Push(Vector2(35.f, 0));
	}
	if (Application::IsKeyPressed('L'))
	{
		gameObjects[0]->getRigidBody()->GetPhysicsCompt()->Push(Vector2(0.f, 1400));
	}
	if (Application::Button_Left)
	{
	//	mL_state = true;
		m_state = true;

	}
	if (Application::Button_Right)
	{
	//	mR_state = true;
	}

	gameObjects[0]->checkColision(gameObjects[1]);
	gameObjects[0]->checkColision(gameObjects[3]);
	//gameObjects[0]->checkColision(gameObjects[4]);
	//gameObjects[0]->checkColision(gameObjects[5]);
	//gameObjects[0]->checkColision(gameObjects[6]);

	//m_GUI->Update(dt);

	//ctrs->Update(this, gameObjects, mL_state, mR_state, dt);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update(dt);
	}

	cursor->Update(dt, m_state);

	
}

void CTutorialScene::Render()
{
	CSceneManager2D::Render();

	modelStack.PushMatrix();
	//RenderMeshIn2D(meshList[GEO_BG], false);
	modelStack.PopMatrix();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render(this);
	}
	//m_GUI->Render(this);
	//ctrs->Render(this);
	cursor->Render(this);
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