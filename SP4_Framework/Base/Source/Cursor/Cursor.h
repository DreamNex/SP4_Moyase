#pragma once

#include"../Application.h"
#include"Vector2.h"
#include "GL\glew.h"
#include "../LoadTGA.h"
#include"../Mesh.h"
#include "../MeshBuilder.h"
#include "../GUIManager/GUIManager.h"
#include "../GameObjects/GameObject.h"

class Cursor
{
public:
	Cursor( char * d_cursorMesh, char * clickedMesh, char * tailmesh, float mouseSens, float cursSize_x, float cursSize_y);
	~Cursor();

	void Update(float dt, bool m_state);
	void Render(CSceneManager2D* SceneManager2D);

	//Acessors
	Vector2 GetCursPos();
	float  GetMousSens();
	bool  GetMousState();
	
	//Mutators
	void  SetCursPos(Vector2 cursPos);
	void SetMousSens(float mouseSens);
	void SetMousStat(bool    m_state);
	bool CheckCO(std::vector<GUI*> m_gui);
	bool CheckCO(std::vector<GameObject*>LevelAssets);

private:
	Vector2 cursorPos;
	Vector2 oldPos;
	float cursSize_x; 
	float cursSize_y;
	Vector2 min;
	Vector2 max;
	float mouseSens;
	bool m_state;
	Mesh* d_cursorMesh;
	Mesh* clickedMesh;
	Mesh* TailMesh;
	float tspeed;

	std::vector<Vector2*>tailpos;
};

