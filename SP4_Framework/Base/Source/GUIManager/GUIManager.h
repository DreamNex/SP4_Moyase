#pragma once
#include "../ButtonUI.h"
#include <vector>


class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	std::vector<ButtonUI*> m_GUI;

	void CreateGUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText);
	
	void Update(float dt, float mousex, float mousey);

	void Render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol);


};

