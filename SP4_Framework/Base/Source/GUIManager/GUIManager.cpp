#include "GUIManager.h"
#include "../RigidBody/Box.h"

GUIManager::GUIManager(int cannon, int boost , int slow)
{
	Vector2 cannonPos(1200, 200);
	Vector2 slowPos(1200, 350);
	Vector2 boostPos(1200, 500);
	tools[0] = new GUI(cannonPos, GUI::CANNONGUI, new Box(cannonPos, 50, 50), "Mesh", "HoverMesh");
	tools[1] = new GUI(boostPos, GUI::BOOSTGUI, new Box(boostPos, 50, 50), "Mesh", "HoverMesh");
	tools[2] = new GUI(slowPos, GUI::SLOWGUI, new Box(slowPos, 50, 50), "Mesh", "HoverMesh");

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
	for (unsigned int i = 0; i < 3; i++)
	{
		if (tools[i]->GetActive())
		{
			tools[i]->render(SceneManager2D);
		}
	}
}