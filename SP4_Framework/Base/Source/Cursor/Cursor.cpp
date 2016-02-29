#include "Cursor.h"
#include "../RigidBody/CollisionHandler.h"

Cursor::Cursor(char * d_cursorMesh, char * clickedMesh, char * tailmesh, float mouseSens, float cursSize_x, float cursSize_y)
{
	//Constructor
	this->cursorPos = Vector2(Application::mouse_current_x,Application::mouse_current_y);
	this->mouseSens = mouseSens;
	this->cursSize_x = cursSize_x;
	this->cursSize_y = cursSize_y;

	this->d_cursorMesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	this->d_cursorMesh->textureID = LoadTGA(d_cursorMesh);

	this->clickedMesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	this->clickedMesh->textureID = LoadTGA(clickedMesh);

	this->TailMesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	this->TailMesh->textureID = LoadTGA(tailmesh);

	this->min.Set(cursorPos.x - (cursSize_x * 0.5f), cursorPos.y - (cursSize_y * 0.5f));
	this->max.Set(cursorPos.x + (cursSize_x * 0.5f), cursorPos.y + (cursSize_y * 0.5f));

	m_state = false;
	this->oldPos = Vector2(0, 0);
	
	this->tailpos.push_back(new Vector2(cursorPos.x, cursorPos.y));
	this->tailpos.push_back(new Vector2(cursorPos.x, cursorPos.y));
	this->tailpos.push_back(new Vector2(cursorPos.x, cursorPos.y));
}


Cursor::~Cursor()
{
	//Destructor
	for (unsigned int i = 0; i < tailpos.size(); i++)
	{
		if (tailpos[i] != NULL)
		{
			delete tailpos[i];
			tailpos[i] = NULL;
		}
	}
}

void Cursor::Update(float dt, bool m_state)
{
	Vector2 dir;
	for (unsigned int i = 0; i < tailpos.size(); ++i)
	{
		dir = cursorPos - (*tailpos[i]);
		float dist = dir.Length();
		if (dist > 1)
		{
			dir.Normalized();
			(*tailpos[i]) = (*tailpos[i]) + dir.Normalized() * dt * dist * (i+1*5);
		}
	}
	
	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	if (oldPos.LengthSquared() != 0)
	{

		if (mousePos != oldPos)//when moving
		{
			//Calculate Mouse Change
			Vector2 MouseChange;
			MouseChange = mousePos - oldPos;
			Vector2 MoveCursor = MouseChange * 1.0f;
			cursorPos = MoveCursor + cursorPos;
			
		} 
		this->m_state = m_state;
	}
	oldPos = mousePos;	
}

void Cursor::Render(CSceneManager2D* SceneManager2D)
{
	for (unsigned int i = 0; i < tailpos.size(); ++i)
	{
		SceneManager2D->RenderMeshIn2D(TailMesh, false, cursSize_x, cursSize_y, (*tailpos[i]).x - cursSize_x / 2, (*tailpos[i]).y - cursSize_y / 2, 1);
	}
	if (m_state)
		SceneManager2D->RenderMeshIn2D(clickedMesh, false, cursSize_x, cursSize_y, cursorPos.x - cursSize_x/2 , cursorPos.y-cursSize_y/2, 2);
	else
		SceneManager2D->RenderMeshIn2D(d_cursorMesh, false, cursSize_x, cursSize_y, cursorPos.x - cursSize_x / 2, cursorPos.y - cursSize_y / 2, 2);

}

//Acessors
Vector2 Cursor::GetCursPos()
{
	return cursorPos;
}
float Cursor::GetMousSens()
{
	return mouseSens;
}
bool Cursor::GetMousState()
{
	return m_state;
}

//Mutators
void Cursor::SetCursPos(Vector2 cursPos)
{
	this->cursorPos = cursPos;
}

void Cursor::SetMousSens(float mouseSens)
{
	this->mouseSens = mouseSens;
}
void Cursor::SetMousStat(bool m_state)
{
	this->m_state = m_state;
}

bool Cursor::CheckCO(std::vector<GUI*> m_gui)
{
	for (unsigned int i = 0; i<m_gui.size(); ++i)
	{
			if (m_gui[i]->GetPos().x > min.x
				&& m_gui[i]->GetPos().x  < max.x
				&& m_gui[i]->GetPos().y > min.y
				&& m_gui[i]->GetPos().y < max.y)
			{
				return true;
			}
			else
				return false;
	}
	
}
bool Cursor::CheckCO(std::vector<GameObject*>LevelAssets)
{
	for (unsigned int i = 0; i<LevelAssets.size(); ++i)
	{
		if (LevelAssets[i]->getPos().x > min.x
			&& LevelAssets[i]->getPos().x < max.x
			&& LevelAssets[i]->getPos().y > min.y
			&& LevelAssets[i]->getPos().y < max.y)
		{
			return true;
		}

		else
			return false;
	}
}