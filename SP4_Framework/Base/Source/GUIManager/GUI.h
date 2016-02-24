#pragma once
#include "Vector2.h"
#include "../RigidBody/CollisionComponent.h"
#include "../MeshBuilder.h"
#include "../Scenes\SceneManager2D.h"
#include <vector>

class GUI 
{

public:
	enum GUITYPEID
	{
		CANNONGUI,
		SLOWGUI,
		BOOSTGUI,
		STARTGUI,
		EXIT
	};

	GUI(Vector2 pos, int g_typeID, CollisionComponent * gui_Bound, char *Mesh, char * hoverMesh);
	~GUI();

	void render(CSceneManager2D* SceneManager2D);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ACCESSORS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bool GetActive();
	int GetType();
	Vector2 GetPos();
	CollisionComponent* GetGUIBound();
	bool CheckMO(Vector2);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MUTATORS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void SetActive(bool Active);
	void SetType(int g_typeID);
	void SetPos(Vector2 pos);
	void SetGUIBound(CollisionComponent * gui_Bound);

private:
	bool BtnIsActive;
	int g_typeID;
	bool MO;
	Mesh* Mesh, *hoverMesh;
	Vector2 pos;
	CollisionComponent* gui_Bound;
};

