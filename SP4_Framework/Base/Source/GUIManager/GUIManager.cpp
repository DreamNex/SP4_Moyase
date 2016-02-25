#include "GUIManager.h"
#include "../RigidBody/Box.h"

GUIManager::GUIManager(int cannon, int boost , int slow)
{
	Vector2 cannonPos(1180, 200);
	Vector2 slowPos(1180, 350);
	Vector2 boostPos(1180, 500);
	Vector2 startPos(550, 600);
	Vector2 ExitPos(10, 660);

	GUI* temp;
	//Cannon
	temp = new GUI(cannonPos, GUI::CANNONGUI, new Box(cannonPos, 80, 80), "Image//cannonGUI.tga", "Image//cannonGUIFaded.tga");
	gui_Tools.push_back(temp);
	gui_toolCount.push_back(cannon);

	//Boost
	temp = new GUI(boostPos, GUI::BOOSTGUI, new Box(boostPos, 80, 80), "Image//boostGUI.tga", "Image//boostGUIFaded.tga");
	gui_Tools.push_back(temp);
	gui_toolCount.push_back(boost);

	//Slow
	temp = new GUI(slowPos, GUI::SLOWGUI, new Box(slowPos, 80, 80), "Image//slowGUI.tga", "Image//slowGUIFaded.tga");
	gui_Tools.push_back(temp);
	gui_toolCount.push_back(slow);

	//Start
	temp = new GUI(startPos, GUI::STARTGUI, new Box(startPos, 180, 100), "Image//startbtn.tga", "Image//slowGUIFaded.tga");
	gui_Tools.push_back(temp);

	//Exit
	temp = new GUI(ExitPos, GUI::EXIT, new Box(ExitPos, 80, 50), "Image//exitbtn.tga", "Image//slowGUIFaded.tga");
	gui_Tools.push_back(temp);

}


GUIManager::~GUIManager()
{
}


std::vector<GUI*> GUIManager::GetTools()
{
	return this->gui_Tools;
}
std::vector<int> GUIManager::GetToolCount()
{
	return this->gui_toolCount;
}

void GUIManager::Update(float dt)
{
	for (unsigned int i = 0; i < gui_toolCount.size(); i++)
	{
		if (gui_toolCount[i] == 0)
		{
			gui_Tools[i]->SetActive(false);
		}
	}

	for (unsigned int i = 0; i < gui_Tools.size(); i++)
	{
		if (gui_Tools[i]->GetActive())
		{
			gui_Tools[i]->CheckMO(Vector2(Application::mouse_current_x, Application::mouse_current_y));
		}
	}
}


void GUIManager::SetToolCount(int index, int val)
{
	gui_toolCount[index] = val;
}
void GUIManager::Render(CSceneManager2D* SceneManager2D)
{
	for (unsigned int i = 0; i < gui_Tools.size(); i++)
	{
		if (gui_Tools[i]->GetActive())
		{
			gui_Tools[i]->render(SceneManager2D);
		}
	}
}