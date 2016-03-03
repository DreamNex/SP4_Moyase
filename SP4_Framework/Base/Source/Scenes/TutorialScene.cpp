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
	if (cursor)
		delete cursor;
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

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GameBG", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//Tits//GameBG.tga");

	meshList[GEO_MO] = MeshBuilder::Generate2DMesh("MO Tut", Color(1, 1, 1), 0, 0, 500, 200);
	meshList[GEO_MO]->textureID = LoadTGA("Image//MO.tga");

	meshList[GEO_PLAY] = MeshBuilder::Generate2DMesh("play Tut", Color(1, 1, 1), 0, 0, 500, 200);
	meshList[GEO_PLAY]->textureID = LoadTGA("Image//Play.tga");

	meshList[GEO_RESET] = MeshBuilder::Generate2DMesh("reset Tut", Color(1, 1, 1), 0, 0, 500, 200);
	meshList[GEO_RESET]->textureID = LoadTGA("Image//Reset.tga");

	meshList[GEO_GUI1] = MeshBuilder::Generate2DMesh("gui1 Tut", Color(1, 1, 1), 0, 0, 500, 200);
	meshList[GEO_GUI1]->textureID = LoadTGA("Image//gui1.tga");

	meshList[GEO_DRAG] = MeshBuilder::Generate2DMesh("drag Tut", Color(1, 1, 1), 0, 0, 500, 200);
	meshList[GEO_DRAG]->textureID = LoadTGA("Image//drag.tga");

	meshList[GEO_ROT] = MeshBuilder::Generate2DMesh("rotate Tut", Color(1, 1, 1), 0, 0, 500, 200);
	meshList[GEO_ROT]->textureID = LoadTGA("Image//rotate.tga");

	meshList[GEO_WIN] = MeshBuilder::Generate2DMesh("dyk Tut", Color(1, 1, 1), 0, 0, 400, 500);
	meshList[GEO_WIN]->textureID = LoadTGA("Image//dyk.tga");

	meshList[GEO_CLR] = MeshBuilder::Generate2DMesh("clr Tut", Color(1, 1, 1), 0, 0, 800, 320);
	meshList[GEO_CLR]->textureID = LoadTGA("Image//Clear.tga");

	meshList[GEO_MM] = MeshBuilder::Generate2DMesh("mm Tut", Color(1, 1, 1), 0, 0, 800, 320);
	meshList[GEO_MM]->textureID = LoadTGA("Image//MM.tga");

	gameObjects.push_back(new Wall(Vector2((float)m_window_width *0.5f, 100.f), (float)m_window_width, 100.f));
	gameObjects.push_back(new Wall(Vector2((float)m_window_width * 0.5f, (float)m_window_height * 0.2f), 100.f, (float)m_window_height - 100.f));
	gameObjects.push_back(new Exito(Vector2((float)m_window_width * 0.95, (float)m_window_height * 0.3f), 100.f,100.f));

	getBall = new Balls(Vector2(300, 700), 50, "Image//Avatars//Avatar_5.tga");
	 
	cursor = new Cursor("Image//curshead.tga", "Image//curshead2.tga","Image//curstail.tga", 1.5f, 20, 20);
	m_GUI = new GUIManager(9,9,9);
	ctrs = new Controls(m_GUI);
	G_States = RESET;

	MO = false;
	play = false;
	rplay = false;
	vreset = false;
	gui = false;
	drag = false;
	rotate = false;
	win = false;
	onClick = false;
	clear = false;
	mm = false;
	temp = false;
	T_States = MOver;

	transition = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true);
}

void CTutorialScene::Update(double dt)
{
	//Check which state
	G_States = static_cast<GameStates>(ctrs->GetState());

	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	bool mL_state = false;
	bool mR_state = false;

	if (Application::Button_Left)
	{
		mL_state = true;

	}
	if (Application::Button_Right)
	{
		mR_state = true;
	}
	
	switch (G_States)
	{
	case RESET:
	{
		getBall->reset();
		m_GUI->Update(dt);
		ctrs->Update(this, gameObjects, mL_state, mR_state, dt);
		break;
	}
	case START:
	{
		m_GUI->Update(dt);

		ctrs->Update(this, gameObjects, mL_state, mR_state, dt, true);

		getBall->update(dt);
		for (unsigned int i = 0; i < gameObjects.size();++i)
		{
			getBall->checkColision(gameObjects[i]);
		}
		
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->update(dt);
		}

		if (G_States == RESET)
		{
			ctrs->SetState(0);
		}
		break;
	}
	case EXIT:
	{
		getBall->reset();
		break;
	}
	default:
		break;
	}

	if (getBall->checkColision(gameObjects[0]))
	{
		G_States = RESET;
	}

	switch (T_States)
	{
	case MOver:
	{
		MO = true;
		if (Application::mouse_current_y <= m_window_height*0.03)
		{
			MO = false;
			T_States = PLAY;
		}
		break;
	}
	case PLAY:
	{
		play = true;
		if (Application::mouse_current_y <= m_window_height*0.1 && mL_state == true)
		{
			play = false;
			T_States = TRESET;
		}
		break;
	}
	case TRESET:
	{
		if (!mL_state)
		{
			onClick = true;
		}
		if (onClick)
		{
			vreset = true;
			if (Application::mouse_current_y <= m_window_height*0.1 && mL_state == true)
			{
				vreset = false;
				onClick = false;
				T_States = GUI;
			}
		}
		break;
	}
	case GUI:
	{
		gui = true;
		if (Application::mouse_current_y <= m_window_height*0.1 && (Application::mouse_current_x >= m_window_width-430 && Application::mouse_current_x <= m_window_width-360) && mL_state == true)
		{
			gui = false;
			T_States = DRAGHERE;
		}
		break;
	}
	case DRAGHERE:
	{
		drag = true;
		if ((Application::mouse_current_y <= m_window_height-200 && Application::mouse_current_y >= m_window_height-350) && (Application::mouse_current_x >= m_window_width/5 && Application::mouse_current_x <= m_window_width/3) && !mL_state)
		{
			drag = false;
			T_States = RPLAY;
		}
		break;
	}
	case RPLAY:
	{
		play = true;
		if (Application::mouse_current_y <= m_window_height*0.1 && mL_state == true)
		{
			play = false;
			T_States = RPLAY2;
		}
		break;
	}
	case RPLAY2:
	{
		if (!mL_state)
		{
			onClick = true;
		}
		if (onClick)
		{
			vreset = true;
			if (Application::mouse_current_y <= m_window_height*0.1 && mL_state == true)
			{
				vreset = false;
				onClick = false;
				T_States = ROTATE;
			}
		}
		break;
	}
	case ROTATE:
	{
		rotate = true;
		if ((Application::mouse_current_y <= m_window_height - 200 && Application::mouse_current_y >= m_window_height - 350) && (Application::mouse_current_x >= m_window_width / 5 && Application::mouse_current_x <= m_window_width / 3) && mR_state)
		{
			rotate = false;
			T_States = RPLAY3;
		}
		break;
	}
	case RPLAY3:
	{
		play = true;
		if (Application::mouse_current_y <= m_window_height*0.1 && mL_state == true)
		{
			play = false;
			T_States = CLEAR;
		}
		break;
	}
	case CLEAR:
	{
		if (!mL_state)
		{
			onClick = true;
		}
		if (onClick)
		{
			win = true;
			if (mL_state)
			{
				win = false;
				onClick = false;
				T_States = END;
			}
		}
		break;
	}
	case END:
	{
		if (!mL_state)
		{
			onClick = true;
		}
		if (onClick)
		{
			clear = true;
			if (mL_state)
			{
				clear = false;
				T_States = TPLAY;
			}
		}
		break;
	}
	case TPLAY:
	{
		if (getBall->checkColision(gameObjects[2]))
		{
			mm = true;	
			temp = true;
		}
		if(mL_state && temp)
		{
			mm = false;
			//go back main menu
		}
		break;
	}

	default:
		break;
	}
	
}

void CTutorialScene::Render()
{
	CSceneManager2D::Render();



	RenderMeshIn2D(meshList[GEO_BG], false, 1.f, 1.f, 0.f, 0.f, -1.f);

	getBall->render(this);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render(this);
	}
	m_GUI->Render(this);
	ctrs->Render(this);

	if (MO)
	{
		RenderMeshIn2D(meshList[GEO_MO], false, 1.f, 1.f, m_window_width*0.3f, m_window_height*0.05f, 0.f);
	}
	else if (play)
	{
		RenderMeshIn2D(meshList[GEO_PLAY], false, 1.f, 1.f, m_window_width*0.3f, m_window_height*0.13f, 0.f);
	}
	else if (vreset)
	{
		RenderMeshIn2D(meshList[GEO_RESET], false, 1.f, 1.f, m_window_width*0.3f, m_window_height*0.13f, 0.f);
	}
	else if (gui)
	{
		RenderMeshIn2D(meshList[GEO_GUI1], false, 1.f, 1.f, m_window_width*0.36f, m_window_height*0.13f, 0.f);
	}
	else if (drag)
	{
		RenderMeshIn2D(meshList[GEO_DRAG], false, 1.f, 1.f, m_window_width*0.18f, m_window_height*0.5f, 0.f);
	}
	else if (rotate)
	{
		RenderMeshIn2D(meshList[GEO_ROT], false, 1.f, 1.f, m_window_width*0.18f, m_window_height*0.5f, 0.f);
	}
	else if (win)
	{
		RenderMeshIn2D(meshList[GEO_WIN], false, 1.f, 1.f, m_window_width*0.35, m_window_height*0.2, 0.f);
	}
	else if (clear)
	{
		RenderMeshIn2D(meshList[GEO_CLR], false, 1.f, 1.f, m_window_width*0.2, m_window_height/2, 0.f);
	}
	else if (mm)
	{
		RenderMeshIn2D(meshList[GEO_MM], false, 1.f, 1.f, m_window_width*0.2, m_window_height / 2, 0.f);
	}

	transition->render(this, 5);
}

void CTutorialScene::vExit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}