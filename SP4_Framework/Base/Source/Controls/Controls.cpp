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

void Controls::OnClick(Vector2 mousePos, std::vector<GameObject*>&gu)
{
	switch (c_state)
	{
	case SELECTION:
	{
		for (unsigned int i = 0; i < m_GUI->m_GUI.size(); ++i)
		{
			if (m_GUI->m_GUI[i]->CheckMouseOver(mousePos.x, mousePos.y))
			{
				b_Drag = true;
				//create a non-placed tool here....
				if (m_GUI->m_GUI[i]->GetType() == GUI::CANNONGUI)
				{
					// Create greycannon
					cannon = new Cannon(Vector2(mousePos), 50, 50);
					gu.push_back(cannon);
					c_state = PLACEMENT;
				}
				else if (m_GUI->m_GUI[i]->GetType() == GUI::SLOWGUI)
				{
					// Create greyslow
					slow = new Slow(Vector2(mousePos), 50, 50);
					gu.push_back(slow);
					c_state = PLACEMENT;
				}
				else if (m_GUI->m_GUI[i]->GetType() == GUI::BOOSTGUI)
				{
					//Create greyboost
					boost = new Boost(Vector2(mousePos), 50, 50);
					gu.push_back(boost);
					c_state = PLACEMENT;
				}
			}
			SelctedGO = GetSelection(mousePos);
			
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
		break;
	}

	default:
		break;
	}
}

void Controls::OnDrag(Vector2 MOUSEPOS)
{
	/*if (b_Drag)
	{
		SelctedGO->setPosition(MOUSEPOS);
		
	}*/
}

GameObject* Controls::GetSelection(Vector2 mousePos)
{
	for (unsigned int i = 0; i < m_GUI->m_GUI.size();++i) 
	{
		if (m_GUI->m_GUI[i]->CheckMouseOver(mousePos.x, mousePos.y))
		{
			switch (m_GUI->m_GUI[i]->GetType())
			{
				case GUI::CANNONGUI:
				{
					cannon = new Cannon(Vector2(mousePos), 50, 50);
					break;
				}
				case GUI::BOOSTGUI:
				{
					boost = new Boost(Vector2(mousePos), 50, 50);
					break;
				}
				case GUI::SLOWGUI:
				{
					slow = new Slow(Vector2(mousePos), 50, 50);
					break;
				}
			}

		}
	}
	CollisionHandler ch;
	Circle* mouseBound = new Circle(mousePos, 0.1f);
	for (unsigned int i = 0; i < g_Obj.size(); ++i)
	{
		if (ch.CheckCollision(g_Obj[i]->getRigidBody()->GetCollisionCompt(), mouseBound))//if mouse and game object collide
		{
			return g_Obj[i];
		}
	}
	GameObject* temp = 0;
	return temp;
}
