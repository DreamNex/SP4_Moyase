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
GameObject* Controls::Update(CSceneManager2D* sm, std::vector<GameObject*> levelAssets, Vector2 mousePos, bool m_state, float dt, Vector2 test)
{
	GameObject* temp = 0;
	switch (c_state)
	{
	case SELECTION:
		if (m_state)//Clicked
		{ 
			if (GetSelection(levelAssets, mousePos))//Obtained a Selected GO
			{ 
				c_state = PLACEMENT;
			}
		}
		break;
	case PLACEMENT:
		mousePos.y = 720 - mousePos.y;
		SelectedGO->setPosition(mousePos);
		if (!m_state)
		{
			if (GetPlacement(levelAssets, mousePos))//Can place object with no obstructions
			{
				if (!SelectedActive)
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
	for (unsigned int i = 0; i < 3; ++i)
	{
		Box* temp = (Box*)m_GUI->GetTools(i)->GetGUIBound();
		if (((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
			&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y)))
		{
			SelectedActive = false;
			switch (m_GUI->GetTools(i)->GetType())
			{
			case 0:
			{
				SelectedGO = new Cannon(mousePos,50,50);
				break;
			}
			case 1:
			{
				SelectedGO = new Boost(mousePos, 50, 50);
				break;
			}
			case 2:
			{
				SelectedGO = new Slow(mousePos, 50, 50);
				break;
			}
			default:
				break;
			}
			return true;
		}
	}
	for (unsigned int i = 1; i < levelAssets.size(); ++i)
	{
		if (dynamic_cast<Tools*>(levelAssets[i]))
		{
			Box* temp = (Box*)levelAssets[i]->getRigidBody()->GetCollisionCompt();
			if (((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
				&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y)))//if mouse and game object collide
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
	//((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
		//&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y))
	for (unsigned int i = 1; i < levelAssets.size(); ++i)//Check if Collide with anything
	{
		if (SelectedIndex == i)
			continue;
		if (cH.CheckCollision(SelectedGO->getRigidBody()->GetCollisionCompt(), levelAssets[i]->getRigidBody()->GetCollisionCompt()))
		{
			noCollide = false;
			break;
		}
	}
	if (noCollide)
		Vector2 Temp;
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