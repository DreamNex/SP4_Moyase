#include "GUIManager.h"
#include "../RigidBody/Box.h"

GUIManager::GUIManager(int cannon, int boost , int slow)
{
	Vector2 panelPos(900, 10);
	Vector2 cannonPos = panelPos + Vector2(150, 100);
	Vector2 slowPos = panelPos + Vector2(50, 50);
	Vector2 boostPos = panelPos + Vector2(50, 150);
	Vector2 startPos = panelPos + Vector2(50, 250);
	Vector2 ExitPos = panelPos + Vector2(50, 350);
	Vector2 pointerPos = panelPos + Vector2(-50, 180);

	slideLength = Vector2(0, 200);
	sL_copy = slideLength;
	slide = false;
	disablePanel = false;

	panel = new GUI(panelPos, GUI::PANEL, new Box(panelPos, 250, 400), "", "");
	slidePointer = new GUI(pointerPos, GUI::POINTER, new Box(pointerPos, 50, 50), "Image//cannonGUI.tga", "");

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
	temp = new GUI(startPos, GUI::STARTGUI, new Box(startPos, 100, 100), "Image//startbtn.tga", "Image//slowGUIFaded.tga");
	gui_Tools.push_back(temp);

	//Reset
	temp = new GUI(startPos, GUI::RESETGUI, new Box(startPos, 180, 100), "Image//Resetbtn.tga", "Image//slowGUIFaded.tga");
	gui_Tools.push_back(temp);
	gui_Tools.back()->SetActive(false);

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
		{	gui_Tools[i]->SetActive(false);
		}
	}

	std::vector<GUI*> slide_GUI;

	if (!disablePanel)
	{ 
		CheckPointer();
	}

	slide_GUI.push_back(panel);
	slide_GUI.push_back(slidePointer);
	

	panel->Update();
	slidePointer->Update();

	for (unsigned int i = 0; i < gui_Tools.size(); i++)
	{
		if (gui_Tools[i]->GetActive())
		{
			gui_Tools[i]->CheckMO();
		}
		slide_GUI.push_back(gui_Tools[i]);
		gui_Tools[i]->Update();
	}
	Slide(slide_GUI, 8 );
}

void GUIManager::SetToolCount(int index, int val)
{
	gui_toolCount[index] = val;
}

bool GUIManager::CheckPointer()
{
	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	if (slidePointer->GetPos().y >= mousePos.y)
		slide = true;
	else
		slide = false;
	return false;
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
	panel->render(SceneManager2D);
	slidePointer->render(SceneManager2D);
}

void GUIManager::Slide(std::vector<GUI*> gui, float slideScalar)
{
	Vector2 slideDist = sL_copy.Normalized() * slideScalar;
	if (!slide || disablePanel)//Slide Out of Game
	{
		if (slideLength.LengthSquared() != sL_copy.LengthSquared())
		{
			Vector2 slideBy(0, 0);
			if ((slideLength + slideDist).LengthSquared() >= sL_copy.LengthSquared())
			{
				Vector2 slideOffset = sL_copy - slideLength;
				slideBy = slideOffset;
				slideLength = sL_copy;
			}
			else
			{ 
				slideBy = slideDist;
				slideLength = slideLength + slideDist;
			}
			for (unsigned int i = 0; i < gui.size(); ++i)
				gui[i]->SetPos(gui[i]->GetPos() - slideBy);
		}
	}
	else if (slide)//Slide Into Game
	{
		if (slideLength.LengthSquared() != 0)
		{
			Vector2 slideBy(0, 0);
			if (slideLength.LengthSquared() <= slideDist.LengthSquared())
			{
				Vector2 slideOffset = slideDist - slideLength;
				slideBy = slideOffset;
				slideLength = Vector2(0, 0);
			}
			else if (slideLength.LengthSquared() > slideDist.LengthSquared())
			{
				slideBy = slideDist;
				slideLength = slideLength - slideDist;
			}
			for (unsigned int i = 0; i < gui.size(); ++i)
				gui[i]->SetPos(gui[i]->GetPos() + slideBy);
		}
	}
}

void GUIManager::SetSlide(bool slide)
{
	this->slide = slide;
}