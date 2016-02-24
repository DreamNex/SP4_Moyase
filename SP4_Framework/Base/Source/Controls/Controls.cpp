
#include "Controls.h"
#include "../RigidBody/CollisionHandler.h"
#include"../GameObjects/Balls.h"
#include"../GameObjects/Wall.h"
#include"../GameObjects/Tools.h"
#include"../Application.h"

Controls::Controls(GUIManager * m_GUI)
{
	c_state = SELECTION;
	this->m_GUI = m_GUI;
	SelectedActive = false;
	SelectedGO = NULL;
	mouse_drag = false;
}

Controls::~Controls()
{

}

GameObject* Controls::Update(CSceneManager2D* sm, std::vector<GameObject*> levelAssets, bool m_state, float dt)
{
	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	GameObject* temp = 0;

	//States
	switch (c_state)
	{
	case SELECTION:// check g_obj and GUI
		if (m_state)//Clicked
		{ 
			if (GetSelection(levelAssets, mousePos))//check g_obj collides
			{ 
				if (SelectedGO != NULL)//dun go placement change state
					c_state = PLACEMENT;
			}
		}
		break;
	case PLACEMENT:
		mousePos.y = 720 - mousePos.y;
		SelectedGO->setPosition(mousePos);
		if (!m_state)
		{
			if (GetPlacement(levelAssets, mousePos) && (!SelectedActive))//Can place object with no obstructions
			{
				temp = SelectedGO;
			}
			else
			{
				
			}
			ResetState();
		}
		break;
	case ROTATION:
		break;
	}
	return temp;
}

bool Controls::GetSelection(std::vector<GameObject*> levelAssets, Vector2 mousePos)
{
	//check m_gui collides
	for (unsigned int i = 0; i < 5; ++i)
	{
		Box* temp = (Box*)m_GUI->GetTools(i)->GetGUIBound();
		if (((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
			&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y)))////if collide create new obj
		{
			SelectedActive = false;
			switch (m_GUI->GetTools(i)->GetType())
			{
			case GUI::CANNONGUI:
			{
				mousePos.y = 720 - mousePos.y;
				SelectedGO = new Cannon(mousePos,50,50);
				break;
			}
			case GUI::BOOSTGUI:
			{
				mousePos.y = 720 - mousePos.y;
				SelectedGO = new Boost(mousePos, 50, 50);
				break;
			}
			case GUI::SLOWGUI:
			{
				
				SelectedGO = new Slow(mousePos, 50, 50);
				break;
			}
			case GUI::STARTGUI://changestate to start
			{
				mousePos.y = 720 - mousePos.y;
				SelectedGO = NULL;
				state = 2;
				break;
			}
			case GUI::EXIT://changestate to Exit
			{
				mousePos.y = 720 - mousePos.y;
				SelectedGO = NULL;
				state = 3;
				break;
			}
			default:
				break;
			}
			return true;
		}
	}

	//Check if g_obj collides
	//((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
		//&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y))
	CollisionHandler cH;
	mousePos.y = 720 - mousePos.y;
	CollisionComponent * mouseBound = new Circle(mousePos, 0.1f);
	for (unsigned int i = 1; i < levelAssets.size(); ++i)
	{
		if (dynamic_cast<Tools*>(levelAssets[i]))
		{
			if (cH.CheckCollision(mouseBound, levelAssets[i]->getRigidBody()->GetCollisionCompt()))//if mouse and game object collide
			{
				SelectedIndex = i;
				SelectedActive = true;
				SelectedGO = levelAssets[i];
				oldPos = SelectedGO->getPos();
				return true;
			}
		}
	}
	return false;
}

bool Controls::GetPlacement(std::vector<GameObject*> levelAssets, Vector2 mousePos)
{
	CollisionHandler cH;
	bool noCollide = true;

	CollisionComponent * mouseBound = new Circle(mousePos, 50.f);

	//((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
		//&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y))
	for (unsigned int i = 1; i < levelAssets.size(); ++i)// check all the obj is level
	{
		if (SelectedIndex == i)
			continue;
		if (cH.CheckCollision(mouseBound, levelAssets[i]->getRigidBody()->GetCollisionCompt()))//Check if Collide with anything
		{
			Vector2 temp = levelAssets[i]->getPos();
			noCollide = false;
			break;
		}
	}
	return noCollide;
}

void Controls::ResetState()
{
	mouse_drag = false;
	SelectedGO = NULL;
	c_state = SELECTION;
}

void Controls::Render(CSceneManager2D *SceneManger2D)
{
	if (SelectedGO)
	{
		SelectedGO->render(SceneManger2D);
	}
}

int Controls::GetState()
{
	return state;
}

