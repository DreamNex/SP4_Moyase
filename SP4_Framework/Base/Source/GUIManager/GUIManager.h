#pragma once
#include "GUI.h"
#include <vector>


class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	std::vector<GUI*> m_GUI;

	void CreateGUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText, GUI::GUITYPEID g_typeID);
	
	void Update(float dt, float mousex, float mousey);

	void Render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol);


};

