#pragma once
#include "../GUIManager/GUI.h"
#include <vector>
#include "../Application.h"


class GUIManager
{
public:
	GUIManager(int cannon, int boost, int slow);
	~GUIManager();

	void Update(float dt);

	void Render(CSceneManager2D* SceneManager2D);

	std::vector<GUI*> GetTools();
	std::vector<int> GetToolCount();

	void SetToolCount(int index, int val);

private:
	std::vector<GUI*> gui_Tools;
	std::vector<int> gui_toolCount;

};

