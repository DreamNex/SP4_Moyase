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

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GameBG", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//Tits//GameBG.tga");


	m_GUI = new GUIManager(gameLevel.getToolsArray()[0], gameLevel.getToolsArray()[1], gameLevel.getToolsArray()[2]);
	ctrs = new Controls(m_GUI);

	play_state = false;
	
	transition = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true);

	//win state stuff
	winStateOpacity = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true, 100);
	resultLayout = new Layout("Image//i_pod.tga", m_window_width * 0.35f, m_window_height * 0.66f, m_window_width * 0.5f, 0);

	Buttons.push_back(new ButtonUI("back"
		, "Image//back.tga", "Image//back_hover.tga"
		, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeX() * 0.1
		, resultLayout->GetPos().x - resultLayout->GetSizeX() / 5.7, resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24
		, 0.6, false));
	Buttons.push_back(new ButtonUI("replay"
		, "Image//replay.tga", "Image//replay_hover.tga"
		, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeX() * 0.1
		, resultLayout->GetPos().x, resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24
		, 0.6, false));
	Buttons.push_back(new ButtonUI("nextLv"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeX() * 0.1
		, resultLayout->GetPos().x + resultLayout->GetSizeX() / 5.7, resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24
		, 0.6, false));
}

void CGameplayScene::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (play_state)
		{ 
			ctrs->PlayPause();
			play_state = false;
		}
	}
	else
		play_state = true;
	if (curentState != S_WIN)
		curentState = static_cast<GameStates>(ctrs->GetState());

	mL_state = mR_state = false;
	bool playPause = false;
	if (Application::Button_Left)
		mL_state = true;
	if (Application::Button_Right)
		mR_state = true;

	switch (curentState)
	{
	case S_RESET:
		gameLevel.SetScore(0);
		gameLevel.GetParticleManager()->Clear();
		gameLevel.getBall()->reset();
		gameLevel.update(dt, true);
		m_GUI->Update(dt);
		m_GUI->UpdateScore(gameLevel.GetScore());
		ctrs->Update(this, gameLevel.getGameObjects(), mL_state, mR_state, dt);
		break;

	case S_STARTED:
		m_GUI->Update(dt);
		m_GUI->UpdateScore(gameLevel.GetScore());
		ctrs->Update(this, gameLevel.getGameObjects(), mL_state, mR_state, dt, true);
		curentState = static_cast<GameStates>(gameLevel.update(dt));
		if (curentState == S_RESET || playPause)
		{
			ctrs->SetState(0);
		}
		break;

	case S_WIN:
		gameLevel.update(dt);
		
		if (winStateOpacity->getTransparent() > 20)
			winStateOpacity->goOpaque(dt, 70);
		if (resultLayout->GetPos().y < m_window_height * 0.5f)
		{
			resultLayout->SetPos(resultLayout->GetPos().x, resultLayout->GetPos().y + dt * m_window_height * 0.4f);
			for (unsigned int i = 0; i < Buttons.size(); ++i)
			{
				Buttons[i]->SetPos(Buttons[i]->GetX(), resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24);
			}
		}
		for (unsigned int i = 0; i < Buttons.size(); ++i)
		{
			if (Buttons[i]->CheckMouseOver((float)Application::mouse_current_x, (float)Application::mouse_current_y));
		}
		break;
	}
}

void CGameplayScene::Render()
{
	CSceneManager2D::Render();

	RenderMeshIn2D(meshList[GEO_BG], false, 1, 1, 0, 0, -1);
	gameLevel.render(this);

	m_GUI->Render(this);

	ctrs->Render(this);

	switch (curentState)
	{
	case S_WIN:
		winStateOpacity->render(this, 3);
		resultLayout->render(this, 4);
		for (unsigned int i = 0; i < Buttons.size(); ++i)
		{
			Buttons[i]->render(this, meshList[GEO_TEXT], Color(0,0,0), 5);
		}
		break;
	}

	transition->render(this, 6);
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