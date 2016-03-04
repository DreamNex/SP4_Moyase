#include "GUI.h"
#include "GL\glew.h"
#include "../LoadTGA.h"
#include "../Application.h"
#include "../RigidBody/CollisionHandler.h"

GUI::GUI(Vector2 pos, int g_typeID, CollisionComponent * gui_Bound, char *Mesh, char * hoverMesh)
	: BtnIsActive(true)
{

	this->pos = pos;
	this->g_typeID = g_typeID;

	if (dynamic_cast<Box*>(gui_Bound) == false)
	{
		gui_Bound = new Box(this->pos, 5, 5);
	}
	else
	{
		this->gui_Bound = dynamic_cast<Box*>(gui_Bound);
		this->gui_Bound->SetOrigin(this->pos);
	}

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

bool GUI::CheckMO()
{
	Vector2 MO = Vector2(Application::mouse_current_x, Application::mouse_current_y);
	CollisionHandler cH;
	if (dynamic_cast<Box*>(gui_Bound))
	{ 
		Box* temp = (Box*)gui_Bound;
		if (cH.POINT_BOX(MO, temp))
			this->MO = true;
		else
			this->MO = false;
	}
	else if (dynamic_cast<Circle*>(gui_Bound))
	{
		Circle* temp = (Circle*)gui_Bound;
		if (cH.POINT_CIRCLE(MO, temp))
			this->MO = true;
		else
			this->MO = false;
	}
	return this->MO;
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

bool GUI::OnClick()
{
	return MO;
}

Mesh* GUI::GetMesh()
{
	return this->Mesh;
}

void GUI::Update()
{
	Box* temp = (Box*)gui_Bound;

	temp->SetMax(temp->GetOrigin() + Vector2(temp->GetWidth() / 2, temp->GetHeight() / 2));
	temp->SetMin(temp->GetOrigin() - Vector2(temp->GetWidth() / 2, temp->GetHeight() / 2));
}

void GUI::render(CSceneManager2D* SceneManager2D, float z)
{
	if (MO)
		SceneManager2D->RenderMeshIn2D(hoverMesh, false, ((Box*)gui_Bound)->GetWidth(), ((Box*)gui_Bound)->GetHeight(), pos.x - ((Box*)gui_Bound)->GetWidth() / 2, pos.y - ((Box*)gui_Bound)->GetHeight()/2, z);
	else
		SceneManager2D->RenderMeshIn2D(Mesh, false, ((Box*)gui_Bound)->GetWidth(), ((Box*)gui_Bound)->GetHeight(), pos.x - ((Box*)gui_Bound)->GetWidth() / 2, pos.y - ((Box*)gui_Bound)->GetHeight() / 2, z);
}