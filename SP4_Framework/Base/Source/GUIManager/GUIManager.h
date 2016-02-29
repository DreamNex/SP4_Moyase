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
	void Slide(std::vector<GUI*> gui, float slideScalar);
	void SetSlide(bool);

	bool CheckPointer();

private:
	//Panel where all the GUI are placed on
	GUI* scoreBar;
	GUI* panel;
	Vector2 slideLength;
	Vector2 sL_copy;

	bool slide;//True if Show, 
	bool disablePanel;

	std::vector<GUI*> gui_Tools;
	std::vector<int> gui_toolCount;

};

