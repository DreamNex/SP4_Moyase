#include "GUIManager.h"


GUIManager::GUIManager()
{
	
}


GUIManager::~GUIManager()
{
}

void GUIManager::CreateGUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText)
{
	ButtonUI *BUTTHOLE = new ButtonUI(text, normalMesh, hoverMesh, sizeX, sizeY, x, y, textScaling, showText);

	m_GUI.push_back(BUTTHOLE);
}

void GUIManager::Update(float dt, float mousex, float mousey)
{
	for (unsigned int i = 0; i < m_GUI.size(); i++)
	{
		m_GUI[i]->CheckMouseOver(mousex,mousey);
	}
}

void GUIManager::Render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol)
{
	for (unsigned int i = 0; i < m_GUI.size(); i++)
	{
		m_GUI[i]->render(SceneManager2D,textMesh,textCol);
	}
}