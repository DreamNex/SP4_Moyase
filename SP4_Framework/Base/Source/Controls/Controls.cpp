#include "Controls.h"
#include "../RigidBody/CollisionHandler.h"
#include"../GameObjects/Balls.h"
#include"../GameObjects/Wall.h"
#include"../GameObjects/Tools.h"

Controls::Controls(GUIManager * m_GUI)
{
	c_state = SELECTION;
	this->m_GUI = m_GUI;
	click_timer.SetDuration(3);
}


Controls::~Controls()
{

}

void Controls::OnClick(Vector2 mousePos, bool m_state, float dt)
{
	if (enableClick == false)
	{
		if (click_timer.Update(dt))
		{
			enableClick = true;
			click_timer.Start();
		}
		return;
	}
	
	switch (c_state)
	{
	case SELECTION:
		{
			if (m_state == true)
			{
				if (GetSelection(mousePos) == true)
				{
					c_state = PLACEMENT;
				}
			}
			break;
		}
		case PLACEMENT:
		{
			SelctedGO->setPosition(mousePos);
			if (m_state == true)
			{
				if (GetPlacement(mousePos) == true)
				{
					c_state = ROTATION;
				}
			}
			break;
		}
		case ROTATION:
		{
			c_state = SELECTION;
			break;
		}
		default:
			break;
		}
}


bool Controls::GetSelection(Vector2 mousePos)
{
	CollisionHandler ch;
	Circle* mouseBound = new Circle(mousePos, 0.1f);

	for (unsigned int i = 0; i < 3; ++i)
	{
		Box* temp = (Box*)m_GUI->GetTools(i)->GetGUIBound();
		if (((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
			&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y)))
		{
			switch (m_GUI->GetTools(i)->GetType())
			{
			case 0:
			{
				SelctedGO = new Cannon(mousePos,50,50);
				break;
			}
			case 1:
			{
				SelctedGO = new Boost(mousePos, 50, 50);
				break;
			}
			case 2:
			{
				SelctedGO = new Slow(mousePos, 50, 50);
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
			if (ch.CheckCollision(levelAssets[i]->getRigidBody()->GetCollisionCompt(), mouseBound))//if mouse and game object collide
			{
				SelctedGO = levelAssets[i];
				return true;
			}
		}
	}

	return false;
}

bool Controls::GetPlacement(Vector2 mousePos)
{
	CollisionHandler ch;
	Circle* mouseBound = new Circle(mousePos, 0.1f);

	bool collided = true;
	for (unsigned int i = 1; i < levelAssets.size(); ++i)
	{
		Box* temp = (Box*)levelAssets[i];
		if (((mousePos.x <= temp->GetMax().x && mousePos.x >= temp->GetMin().x)
			&& (mousePos.y <= temp->GetMax().y && mousePos.y >= temp->GetMin().y)) == false)
		{
			collided = false;
			break;
		}
	}
	return !collided;
}

void Controls::Render(CSceneManager2D *SceneManger2D)
{
	if (SelctedGO)
	{
		SelctedGO->render(SceneManger2D);
	}
}

void Controls::SetLevelAssets(std::vector<GameObject*> levelAssets)
{
	this->levelAssets = levelAssets;
}