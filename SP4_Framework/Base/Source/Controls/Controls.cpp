
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
	state = 0;
	cursor = new Cursor("Image//curshead.tga", "Image//curshead2.tga","Image//curstail.tga", 1.5f, 20, 20);
	
}

Controls::~Controls()
{

}

void Controls::Update(CSceneManager2D* sm, std::vector<GameObject*> &levelAssets, bool ml_state, bool mr_state, float dt, bool guiOnly)
{
	this->mL_state = ml_state;
	this->mR_state = mr_state;

	cursor->Update(dt, mL_state || mR_state); //MouseLeft
	Vector2 mousePos(cursor->GetCursPos().x, cursor->GetCursPos().y );


	if (!guiOnly)
	{
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
			DoRotation(mousePos);
			break;
		}
	}
	else
	{
		GetSelection(mousePos);
	}
}

void Controls::GetSelection(Vector2 mousePos)
{
	if (mL_state)//mouse click
	{
		for (unsigned int i = 3; i < m_GUI->GetTools().size(); ++i)
		{
			if (m_GUI->GetTools()[i]->OnClick(mousePos) && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
			{
				onClicked = true;
				break;
			}
		}
	}
	else if (!mL_state && onClicked)
	{
		//for start and exit
		for (unsigned int i = 3; i < m_GUI->GetTools().size(); ++i)
		{
			cursor->CheckCO(m_GUI->GetTools());
			{
				if (m_GUI->GetTools()[i]->OnClick(mousePos) && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
				{
					switch (m_GUI->GetTools()[i]->GetType())
					{
					case GUI::STARTGUI:
						state = 1;
						m_GUI->GetTools()[i]->SetActive(false);
						if (m_GUI->GetTools()[i]->GetActive() == false)
						{
							m_GUI->GetTools()[GUI::RESETGUI]->SetActive(true);
						}

						break;
					case GUI::EXIT:
						//SelectedGO = new Boost(mousePos, 50, 50);
						state = 2;
					case GUI::RESETGUI:
						state = 0;
						m_GUI->GetTools()[i]->SetActive(false);
						m_GUI->GetTools()[GUI::STARTGUI]->SetActive(true);
					default:
						break;
					}
					break;
				}
				onClicked = false;
			}
		}
	}
}


void Controls::GetSelection(std::vector<GameObject*> &levelAssets, Vector2 mousePos)
{
	if (mL_state)//mouse click
	{
		//for tools
		for (unsigned int i = 0; i < m_GUI->GetToolCount().size(); ++i)//Only 3
		{
			cursor->CheckCO(m_GUI->GetTools());

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

		for (unsigned int i = 3; i < m_GUI->GetTools().size(); ++i)
		{
			if (m_GUI->GetTools()[i]->OnClick(mousePos) && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
			{
				onClicked = true;
				break;
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
		if (SelectedGO)
			c_state = PLACEMENT;
	}
	else if (!mL_state && onClicked)
	{
		//for start and exit
		for (unsigned int i = 3; i < m_GUI->GetTools().size(); ++i)
		{
			cursor->CheckCO(m_GUI->GetTools());

			if (m_GUI->GetTools()[i]->OnClick(mousePos) && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
			{
				switch (m_GUI->GetTools()[i]->GetType())
				{
				case GUI::STARTGUI:
					state = 1;
					m_GUI->GetTools()[i]->SetActive(false);
					if (m_GUI->GetTools()[i]->GetActive() == false)
					{
						m_GUI->GetTools()[GUI::RESETGUI]->SetActive(true);
					}
					break;
				case GUI::EXIT:
					//SelectedGO = new Boost(mousePos, 50, 50);
					state = 2;
					break;
				case GUI::RESETGUI:
					state = 0;
					m_GUI->GetTools()[i]->SetActive(false);
					m_GUI->GetTools()[GUI::STARTGUI]->SetActive(true);
					break;
				default:
					break;
				}
				break;
			}
		}
		onClicked = false;
	}
	else if (mR_state)
	{
		CollisionHandler cH;
		CollisionComponent *mouseBound = new Circle(mousePos, 0.1f);
		for (unsigned int i = 1; i < levelAssets.size(); ++i)
		{
			if (dynamic_cast<Cannon*>(levelAssets[i]))
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
		if (SelectedGO)
			c_state = ROTATION;
	}
}

void Controls::GetPlacement(std::vector<GameObject*> &levelAssets, Vector2 mousePos)
{
	CollisionHandler cH;
	CollisionComponent *mouseBound = new Circle(mousePos, 50.f);

	if (!mL_state)
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

void Controls::DoRotation(Vector2 mousePos)
{
	if (mR_state)
	{
		if (dynamic_cast<Cannon*>(SelectedGO))
		{
			dynamic_cast<Cannon*>(SelectedGO)->getAngleByReference() += (mousePos.x - oldPos.x);
			oldPos = mousePos;
		}
	}
	else
		ResetState();
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
	if (SelectedGO && !SelectedActive)
	{
		SelectedGO->render(SceneManger2D);
	}
	cursor->Render(SceneManger2D);
}

void Controls::SetState(int i)
{
	switch (i)
	{
	case 1:
		state = 1;
		m_GUI->GetTools()[GUI::RESETGUI]->SetActive(true);
		m_GUI->GetTools()[GUI::STARTGUI]->SetActive(false);
		break;

	case 2:
		state = 2;
		break;
		
	case 0:
		state = 0;
		m_GUI->GetTools()[GUI::STARTGUI]->SetActive(true);
		m_GUI->GetTools()[GUI::RESETGUI]->SetActive(false);
		break;
	}
}

int Controls::GetState()
{
	return state;
}