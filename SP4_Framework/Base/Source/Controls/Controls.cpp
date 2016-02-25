
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
	SelectedGO = 0;
}

Controls::~Controls()
{

}

void Controls::Update(CSceneManager2D* sm, std::vector<GameObject*> &levelAssets, bool m_state, float dt)
{
	this->m_state = m_state;
	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	mousePos.y = (float)sm->GetScreenHeight() - mousePos.y;

	//States
	switch (c_state)
	{
	case SELECTION:// check g_obj and GUI
		GetSelection(levelAssets, mousePos);
		break;
	case PLACEMENT:
		GetPlacement(levelAssets, mousePos);
		break;
	case ROTATION:
		GetRotation(mousePos);
		break;
	}
}

void Controls::GetSelection(std::vector<GameObject*> &levelAssets, Vector2 mousePos)
{
	if (m_state)//mouse click
	{
		//for tools
		for (unsigned int i = 0; i < m_GUI->GetToolCount().size(); ++i)//Only 3
		{
			if (m_GUI->GetTools()[i]->OnClick(mousePos) && m_GUI->GetToolCount()[i] > 0)//click on gui
			{
				switch (m_GUI->GetTools()[i]->GetType())
				{
				case GUI::CANNONGUI:
				{
					SelectedGO = new Cannon(mousePos, 50, 50);
					SelectedIndex = 1;
				}
					break;
				case GUI::BOOSTGUI:
				{
					SelectedGO = new Boost(mousePos, 50, 50);
					SelectedIndex = 2;
				}
					break;
				case GUI::SLOWGUI:
				{
					SelectedGO = new Slow(mousePos, 50, 50);
					SelectedIndex = 3;
				}
					break;
				default:
					break;
				}
			}
		}

		//for start and exit
		for (unsigned int i = 3; i < m_GUI->GetTools().size(); ++i)
		{
			if (m_GUI->GetTools()[i]->OnClick(mousePos))//click on gui
			{
				switch (m_GUI->GetTools()[i]->GetType())
				{
				case GUI::STARTGUI:
					state = 1;
					break;
				case GUI::EXIT:
					SelectedGO = new Boost(mousePos, 50, 50);
					state = 2;
				default:
					break;
				}
			}
		}

		CollisionHandler cH;
		CollisionComponent *mouseBound = new Circle(mousePos, 0.1f);
		for (unsigned int i = 1; i < levelAssets.size(); ++i)
		{
			if (dynamic_cast<Tools*>(levelAssets[i]))
			{
				if (cH.CheckCollision(mouseBound, levelAssets[i]->getRigidBody()->GetCollisionCompt()))
				{
					oldPos = levelAssets[i]->getPos();
					SelectedGO = levelAssets[i];
					SelectedActive = true;
					SelectedIndex = i;
				}
			}
		}
	}
	if (SelectedGO)
		c_state = PLACEMENT;
}

void Controls::GetPlacement(std::vector<GameObject*> &levelAssets, Vector2 mousePos)
{
	CollisionHandler cH;
	CollisionComponent *mouseBound = new Circle(mousePos, 50.f);

	if (!m_state)
	{
		if (SelectedActive)//move tool
		{ 
			bool collide = false;
			for (unsigned int i = 1; i < levelAssets.size(); ++i)// check all the obj is level
			{
				if (SelectedIndex == i)
					continue;
				if (cH.CheckCollision(mouseBound, levelAssets[i]->getRigidBody()->GetCollisionCompt()))//Check if Collide with anything
				{
					collide = true;
					break;
				}
			}
			if (collide)
			{
				SelectedGO->setPosition(oldPos);
				ResetState();
			}
			else
			{
				SelectedGO->setPosition(mousePos);
				ResetState();
			}
		}
		else//create tool
		{
			bool collide = false;
			for (unsigned int i = 1; i < levelAssets.size(); ++i)// check all the obj is level
			{
				if (SelectedIndex == i)
					continue;
				if (cH.CheckCollision(mouseBound, levelAssets[i]->getRigidBody()->GetCollisionCompt()))//Check if Collide with anything
				{
					collide = true;
					break;
				}
			}
			if (collide)
			{
				ResetState();
			}
			else
			{
				m_GUI->SetToolCount(SelectedIndex - 1, m_GUI->GetToolCount()[SelectedIndex - 1] - 1);
				SelectedGO->setPosition(mousePos);
				levelAssets.push_back(SelectedGO);
				ResetState();
			}
		}
	}
	else
		SelectedGO->setPosition(mousePos);
}

void Controls::GetRotation(Vector2 mousePos)
{

}

void Controls::ResetState()
{
	SelectedIndex = 0;
	SelectedActive = false;
	oldPos.SetZero();
	SelectedGO = 0;
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

