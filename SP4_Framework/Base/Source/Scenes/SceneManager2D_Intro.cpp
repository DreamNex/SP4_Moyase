#include "SceneManager2D_Intro.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include <sstream>

CSceneManager2D_Intro::CSceneManager2D_Intro()
: SE(NULL)
{
}

CSceneManager2D_Intro::CSceneManager2D_Intro(int m_window_width, int m_window_height)
:
CSceneManager2D(m_window_width, m_window_height)
{
}

CSceneManager2D_Intro::~CSceneManager2D_Intro()
{
	if (SE != NULL)
	{
		SE->drop();
	}

	if (transition)
		delete transition;
}

void CSceneManager2D_Intro::Init()
{
	CSceneManager2D::Init();
	
	SE = createIrrKlangDevice();
	
	meshList[GEO_SPLASH] = MeshBuilder::Generate2DMesh("GEO_SPLASH", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_SPLASH]->textureID = LoadTGA("Image//blaze.tga");
	
	//SE->setSoundVolume(0.1f);
	
	transition = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true);
}

bool a = true;

void CSceneManager2D_Intro::Update(double dt)
{
	CSceneManager2D::Update(dt);

	if (Application::IsKeyPressed(VK_ESCAPE))
	{
		transition->setTransparent(0);
		a = false;
	}
		
	if (a)
	{
		transition->goTransparent(dt, 60);
		if (transition->getTransparent() == 100)
		{
			SE->play2D("SoundTracks//SplashScreen.mp3", false, false);
			a = false;
		}
	}
	else
		transition->goOpaque(dt, 35);
}

void CSceneManager2D_Intro::Render()
{
	CSceneManager2D::Render();

	modelStack.PushMatrix();
	RenderMeshIn2D(meshList[GEO_SPLASH], false);
	modelStack.PopMatrix();

	transition->render(this, 1);

	//On screen text
	//RenderTextOnScreen(CSceneManager2D::meshList[GEO_TEXT], "hello", Color(0, 1, 0), 10, 6, 6);
}

void CSceneManager2D_Intro::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}