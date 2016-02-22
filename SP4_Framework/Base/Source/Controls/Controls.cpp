#include "Controls.h"
#include "../RigidBody/CollisionHandler.h"


Controls::Controls(GUIManager * m_GUI)
{
	c_state = SELECTION;
	this->m_GUI = m_GUI;
	b_Drag = false;
}


Controls::~Controls()
{

}

void Controls::OnClick(Vector2 mousePos)
{
	switch (c_state)
	{
	case SELECTION:
	{
		for (unsigned int i = 0; i < m_GUI->m_GUI.size(); ++i)
		{
			if (m_GUI->m_GUI[i]->GetMouseover())
			{
				b_Drag = true;
				//create a non-placed tool here....
				if (m_GUI->m_GUI[i]->GetType() == GUI::CANNONGUI)
				{
					// Create greycannon
				}
				else if (m_GUI->m_GUI[i]->GetType() == GUI::SLOWGUI)
				{
					// Create greyslow
				}
				else if (m_GUI->m_GUI[i]->GetType() == GUI::BOOSTGUI)
				{
					//Create greyboost
				}
			}
			SelctedGO = GetSelection(mousePos);
			c_state = PLACEMENT;
		}
		break;
	}
	case PLACEMENT:
	{
		//do a bool
		//if bool = false
		//then place
		OnDrag(mousePos);
		break;
	}
	case ROTATION:
	{
		b_Drag = false;
		break;
	}

	default:
		break;
	}
}

void Controls::OnDrag(Vector2 MOUSEPOS)
{
	if (b_Drag)
	{
		SelctedGO->setPosition(MOUSEPOS);
		
	}
}

GameObject* Controls::GetSelection(Vector2 mousePos)
{
	CollisionHandler ch;
	Circle* mouseBound = new Circle(mousePos, 0.1f);
	for (unsigned int i = 0; i < g_Obj.size(); ++i)
	{
		if (ch.CheckCollision(g_Obj[i]->getRigidBody()->GetCollisionCompt(), mouseBound))//if mmouse and game object collide
		{
			return g_Obj[i];
		}
	}
	GameObject* temp = 0;
	return temp;
}
