#pragma once
#include "SceneManager2D.h"
#include "../UI/Layout.h"
#include "irrKlang.h"
using namespace irrklang;

class CSceneManager2D_Intro : public CSceneManager2D
{
public:

	enum GEOMETRY_TYPE
	{
		GEO_SPLASH,
		NUM_GEOMETRY,
	};

	CSceneManager2D_Intro();
	CSceneManager2D_Intro(int m_window_width, int m_window_height);
	~CSceneManager2D_Intro();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	Layout *transition;
private:
	Mesh* meshList[NUM_GEOMETRY];
	ISoundEngine* SE;
	ISound* splash;

};

