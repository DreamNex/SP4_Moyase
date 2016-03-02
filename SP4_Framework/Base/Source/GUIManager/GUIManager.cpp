#include "GUIManager.h"
#include "../RigidBody/Box.h"

GUIManager::GUIManager(int cannon, int boost , int slow)
{
	Vector2 panelPos(640, -40);
	Vector2 cannonPos = panelPos + Vector2(250, 0);
	Vector2 slowPos = panelPos + Vector2(550, 0);
	Vector2 boostPos = panelPos + Vector2(400, 0);
	Vector2 startPos = panelPos + Vector2(0, 2);
	Vector2 ExitPos = panelPos + Vector2(-550, 0);
	Vector2 pointerPos = panelPos + Vector2(0, 52);

	slideLength = Vector2(0, 80);
	sL_copy = slideLength;
	slide = false;
	disablePanel = false;

	panel = new GUI(panelPos, GUI::PANEL, new Box(panelPos, 1280, 80), "Image//panel.tga", "Image//panel.tga");
	scoreBar = new GUI(pointerPos, GUI::POINTER, new Box(pointerPos, 1280, 25), "Image//scoreBar.tga", "Image//scoreBar.tga");
	score = new GUI(pointerPos, GUI::POINTER, new Box(pointerPos, 1, 18), "Image//score.tga", "Image//score.tga");
	toolBar = new GUI(cannonPos + Vector2(0, 20), GUI::POINTER, new Box(cannonPos + Vector2(0, 20), 60, 35), "Image//toolBar.tga", "Image//toolBar.tga");

	GUI* temp;
	//Cannon
	temp = new GUI(cannonPos, GUI::CANNONGUI, new Box(cannonPos, 60, 60), "Image//cannonGUI.tga", "Image//cannonGUIFaded.tga");
	gui_Tools.push_back(temp);
	gui_toolCount.push_back(cannon);

	//Boost
	temp = new GUI(boostPos, GUI::BOOSTGUI, new Box(boostPos, 60, 60), "Image//boostGUI.tga", "Image//boostGUIFaded.tga");
	gui_Tools.push_back(temp);
	gui_toolCount.push_back(boost);

	//Slow
	temp = new GUI(slowPos, GUI::SLOWGUI, new Box(slowPos, 60, 60), "Image//slowGUI.tga", "Image//slowGUIFaded.tga");
	gui_Tools.push_back(temp);
	gui_toolCount.push_back(slow);

	//Start
	temp = new GUI(startPos, GUI::STARTGUI, new Box(startPos, 100, 60), "Image//startbtn.tga", "Image//startbtnFaded.tga");
	gui_Tools.push_back(temp);

	//Reset
	temp = new GUI(startPos, GUI::RESETGUI, new Box(startPos, 100, 60), "Image//Resetbtn.tga", "Image//ResetbtnFaded.tga");
	gui_Tools.push_back(temp);
	gui_Tools.back()->SetActive(false);

	//Exit
	temp = new GUI(ExitPos, GUI::EXIT, new Box(ExitPos, 140, 60), "Image//exitbtn.tga", "Image//exitbtnFaded.tga");
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
			gui_Tools[i]->SetActive(true);
		}
	}

	std::vector<GUI*> slide_GUI;

	if (!disablePanel)
	{ 
		CheckPointer();
	}


	slide_GUI.push_back(scoreBar);
	slide_GUI.push_back(panel);
	slide_GUI.push_back(score);
	slide_GUI.push_back(toolBar);

	panel->Update();
	scoreBar->Update();
	toolBar->Update();

	for (unsigned int i = 0; i < gui_Tools.size(); i++)
	{
		if (gui_Tools[i]->GetActive())
		{
			gui_Tools[i]->CheckMO();
		}
		slide_GUI.push_back(gui_Tools[i]);
		gui_Tools[i]->Update();
	}
	Slide(slide_GUI, 5);
}

void GUIManager::SetToolCount(int index, int val)
{
	gui_toolCount[index] = val;
}

bool GUIManager::CheckPointer()
{
	Vector2 mousePos(Application::mouse_current_x, Application::mouse_current_y);
	if (((Box*)(scoreBar->GetGUIBound()))->GetMax().y >= mousePos.y)
		slide = true;
	else
		slide = false;
	return false;
}

void GUIManager::Render(CSceneManager2D* SceneManager2D)
{
	panel->render(SceneManager2D);
	scoreBar->render(SceneManager2D);
	score->render(SceneManager2D, 3);
	for (unsigned int i = 0; i < gui_Tools.size(); ++i)
	{
		if (gui_Tools[i]->GetActive())
		{
			gui_Tools[i]->render(SceneManager2D, 1);
		}
	}
	

	//ToolBar
	Vector2 originPos = toolBar->GetPos();
	for (unsigned int i = 0; i < gui_toolCount.size(); ++i)
	{
		if (gui_Tools[i]->CheckMO())
		{ 
			 Box* temp = ((Box*)(toolBar));
			 Vector2 moveBy(150 * i, 30);

			for (unsigned int k = 0; k < gui_toolCount[i]; ++k)
			{
				int tempHaha = gui_toolCount[2];
				toolBar->SetPos(toolBar->GetPos() + moveBy);
				toolBar->render(SceneManager2D, 2);
				moveBy.y += temp->GetHeight();
			}
			toolBar->SetPos(originPos);
		}
	}
}

void GUIManager::UpdateScore(int Score)
{
	float scoreLength = (((float)Score) / 20.f) * 1280;
	((Box*)score->GetGUIBound())->SetWidth(scoreLength);
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

void GUIManager::DisablePanel(bool dp)
{
	this->disablePanel = dp;
}