#include "GUIManager.h"
#include "../RigidBody/Box.h"

GUIManager::GUIManager(int cannon, int boost , int slow)
{
	Vector2 cannonPos(1180, 200);
	Vector2 slowPos(1180, 350);
	Vector2 boostPos(1180, 500);
	Vector2 startPos(550, 600);
	Vector2 ExitPos(10, 660);
	tools[0] = new GUI(cannonPos, GUI::CANNONGUI, new Box(cannonPos, 80, 80), "Image//cannonGUI.tga", "Image//cannonGUIFaded.tga");
	tools[1] = new GUI(boostPos, GUI::BOOSTGUI, new Box(boostPos, 80, 80), "Image//boostGUI.tga", "Image//boostGUIFaded.tga");
	tools[2] = new GUI(slowPos, GUI::SLOWGUI, new Box(slowPos, 80, 80), "Image//slowGUI.tga", "Image//slowGUIFaded.tga");
	tools[3] = new GUI(startPos, GUI::STARTGUI, new Box(startPos, 180, 100), "Image//startbtn.tga", "Image//slowGUIFaded.tga");
	tools[4] = new GUI(ExitPos, GUI::EXIT, new Box(ExitPos, 80, 50), "Image//exitbtn.tga", "Image//slowGUIFaded.tga");


	iteraction[0] = cannon;
	iteraction[1] = boost;
	iteraction[2] = slow;
}


GUIManager::~GUIManager()
{
}


void GUIManager::Update(float dt, float mousex, float mousey)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		if (iteraction[i] == 0)
		{
			tools[i]->SetActive(false);
		}
	}

	for (unsigned int i = 0; i <3; i++)
	{
		if (tools[i]->GetActive())
		{
			tools[i]->CheckMO(Vector2(mousex, mousey));
		}
	}
}

GUI *GUIManager::GetTools(int idx)
{
	return tools[idx];
}

void GUIManager::Render(CSceneManager2D* SceneManager2D)
{
	for (unsigned int i = 0; i < 5; i++)
	{
		if (tools[i]->GetActive())
		{
			tools[i]->render(SceneManager2D);
		}
	}
}