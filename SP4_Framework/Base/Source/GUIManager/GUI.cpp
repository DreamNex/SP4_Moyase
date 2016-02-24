#include "GUI.h"
#include "GL\glew.h"
#include "../LoadTGA.h"
#include "../RigidBody/Box.h"

GUI::GUI(Vector2 pos, int g_typeID, CollisionComponent * gui_Bound, char *Mesh, char * hoverMesh)
	: BtnIsActive(true)
{
	this->pos = pos;
	this->g_typeID = g_typeID;
	this->gui_Bound = gui_Bound;
	
	this->Mesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1,1);
	this->Mesh->textureID = LoadTGA(Mesh);

	this->hoverMesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	this->hoverMesh->textureID = LoadTGA(hoverMesh);

	MO = false;
}


GUI::~GUI()
{
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ACCESSORS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool GUI::GetActive()
{
	return BtnIsActive;
}

int GUI::GetType()
{
	return g_typeID;
}
Vector2 GUI::GetPos()
{
	return pos;
}
CollisionComponent* GUI::GetGUIBound()
{
	return gui_Bound;
}

bool GUI::CheckMO(Vector2 MO)
{
	if (pos.x > ((Box*)gui_Bound)->GetMin().x && pos.x < ((Box*)gui_Bound)->GetMax().x && pos.y >((Box*)gui_Bound)->GetMin().y && pos.y < ((Box*)gui_Bound)->GetMax().y)
	{
		MO = true;
		return true;
	}
	else
	{
		MO = false;
		return false;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MUTATORS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void GUI::SetActive(bool Active)
{
	this->BtnIsActive = Active;
}

void GUI::SetType(int g_typeID)
{
	this->g_typeID = g_typeID;
}
void GUI::SetPos(Vector2 pos)
{
	this->pos = pos;
}
void GUI::SetGUIBound(CollisionComponent * gui_Bound)
{
	this->gui_Bound = gui_Bound;
}

void GUI::render(CSceneManager2D* SceneManager2D)
{
	if (MO)
		SceneManager2D->RenderMeshIn2D(hoverMesh, false, ((Box*)gui_Bound)->GetWidth(), ((Box*)gui_Bound)->GetHeight(), pos.x, pos.y);
	else
		SceneManager2D->RenderMeshIn2D(Mesh, false, ((Box*)gui_Bound)->GetWidth(), ((Box*)gui_Bound)->GetHeight(), pos.x, pos.y);
}