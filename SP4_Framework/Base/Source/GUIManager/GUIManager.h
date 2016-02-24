#pragma once
#include "../GUIManager/GUI.h"
#include <vector>


class GUIManager
{
public:
	GUIManager(int cannon, int boost, int slow);
	~GUIManager();

	void Update(float dt, float mousex, float mousey);

	void Render(CSceneManager2D* SceneManager2D);

	GUI * GetTools(int idx);

private:
	int iteraction[3];
	GUI * toolSelection;
	GUI* tools[3];


};

