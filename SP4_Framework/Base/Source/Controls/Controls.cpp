
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
	cursor = new Cursor("Image//Avatars//Avatar_Censored.tga", "Image//Avatars//Avatar_5.tga","Image//Avatars//Avatar_5.tga", 1.5f, 20, 20);
	feedback = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	feedback->textureID = LoadTGA("Image//feedback_wrong.tga");
	correct = true;
}

Controls::~Controls()
{

}

void Controls::Update(CSceneManager2D* sm, std::vector<GameObject*> &levelAssets, bool ml_state, bool mr_state, float dt, bool guiOnly)
{
	this->mL_state = ml_state;
	this->mR_state = mr_state;

	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	m_GUI->Update(dt);

	cursor->Update(dt, mL_state);
	mousePos = cursor->GetCursPos();

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
			if (m_GUI->GetTools()[i]->OnClick() && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
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
			{
				if (m_GUI->GetTools()[i]->OnClick() && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
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
			if (m_GUI->GetTools()[i]->OnClick() && m_GUI->GetToolCount()[i] > 0)//click on gui
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
			if (m_GUI->GetTools()[i]->OnClick() && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
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
		{
			c_state = PLACEMENT;

		}
	}
	else if (!mL_state && !mR_state)
	{
		//switch hovermesh
		CollisionHandler cH;
		CollisionComponent *mouseBound = new Circle(mousePos, 0.1f);
		for (unsigned int i = 1; i < levelAssets.size(); ++i)
		{
			if (dynamic_cast<Tools*>(levelAssets[i]))
			{
				if (cH.CheckCollision(mouseBound, levelAssets[i]->getRigidBody()->GetCollisionCompt()))
				{
					dynamic_cast<Tools*>(levelAssets[i])->setHovering(true);
				}
				else
					dynamic_cast<Tools*>(levelAssets[i])->setHovering(false);
			}
		}

		if (onClicked)
		{
			//for start and exit
			for (unsigned int i = 3; i < m_GUI->GetTools().size(); ++i)
			{
				if (m_GUI->GetTools()[i]->OnClick() && m_GUI->GetTools()[i]->GetActive() == true)//click on gui
				{
					cursor->CheckCO(m_GUI->GetTools());

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
	if (mR_state)
	{
		if (SelectedActive)
		{ 
			if (dynamic_cast<Cannon*>(levelAssets[SelectedIndex]))
				m_GUI->SetToolCount(0, m_GUI->GetToolCount()[0] + 1);
			else if (dynamic_cast<Boost*>(levelAssets[SelectedIndex]))
				m_GUI->SetToolCount(1, m_GUI->GetToolCount()[1] + 1);
			else if (dynamic_cast<Slow*>(levelAssets[SelectedIndex]))
				m_GUI->SetToolCount(2, m_GUI->GetToolCount()[2] + 1);
			levelAssets.erase(levelAssets.begin() + SelectedIndex);
		}
		ResetState();
		return;
	}
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
				correct = true;
				ResetState();
			}
		}
	}
	else
	{
		correct = true;
		SelectedGO->setPosition(mousePos);
		for (unsigned int i = 1; i < levelAssets.size(); ++i)// check all the obj is level
		{
			if (SelectedIndex == i)
				continue;
			if (cH.CheckCollision(mouseBound, levelAssets[i]->getRigidBody()->GetCollisionCompt()))//Check if Collide with anything
			{
				correct = false;
				break;
			}
		}
	}
}

void Controls::DoRotation(Vector2 mousePos)
{
	if (mR_state)
	{
		if (dynamic_cast<Cannon*>(SelectedGO))
		{
			Vector2 toolToMouse = mousePos - SelectedGO->getPos();
			Vector2 up(0, 1);

			float angleBetween = toolToMouse.AngleBetween(up);

			dynamic_cast<Cannon*>(SelectedGO)->getAngleByReference() = (-angleBetween);
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
	if (SelectedGO && correct == false)
	{ 
		Box* temp = (Box*)SelectedGO->getRigidBody()->GetCollisionCompt();
		SceneManger2D->RenderMeshIn2D(feedback, false, temp->GetWidth(), temp->GetHeight(), temp->GetOrigin().x - 23, temp->GetOrigin().y - 23);
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