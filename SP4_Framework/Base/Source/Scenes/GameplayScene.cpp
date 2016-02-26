#include "GameplayScene.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include <sstream>

CGameplayScene::CGameplayScene()
:
gameLevel("", "")
{
}

CGameplayScene::CGameplayScene(int m_window_width, int m_window_height, std::string level, std::string avatar)
:
CSceneManager2D(m_window_width, m_window_height)
, gameLevel(level, avatar)
{
}

CGameplayScene::~CGameplayScene()
{

}

void CGameplayScene::Init()
{
	CSceneManager2D::Init();

	curentState = S_RESET;

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	m_GUI = new GUIManager(gameLevel.getToolsArray()[0], gameLevel.getToolsArray()[1], gameLevel.getToolsArray()[2]);
	ctrs = new Controls(m_GUI);
}

void CGameplayScene::Update(double dt)
{
	if (curentState != S_WIN)
		curentState = static_cast<GameStates>(ctrs->GetState());

	mL_state = mR_state = false;
	
	if (Application::Button_Left)
		mL_state = true;
	if (Application::Button_Right)
		mR_state = true;

	switch (curentState)
	{
	case S_RESET:
		gameLevel.getBall()->reset();
		m_GUI->Update(dt);
		ctrs->Update(this, gameLevel.getGameObjects(), mL_state, mR_state, dt);
		break;

	case S_STARTED:
		m_GUI->Update(dt);
		ctrs->Update(this, gameLevel.getGameObjects(), mL_state, mR_state, dt, true);
		curentState = static_cast<GameStates>(gameLevel.update(dt));
		if (curentState == S_RESET)
		{
			ctrs->SetState(0);
		}
		break;

	case S_WIN:
		gameLevel.update(dt);
		break;
	}
}

void CGameplayScene::Render()
{
	CSceneManager2D::Render();

	gameLevel.render(this);

	m_GUI->Render(this);

	ctrs->Render(this);

	switch (curentState)
	{
	case S_WIN:
		RenderTextOnScreen(meshList[GEO_TEXT], "Win", Color(0, 1, 0), 50, 0, 0);
		break;
	}
}

void CGameplayScene::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}