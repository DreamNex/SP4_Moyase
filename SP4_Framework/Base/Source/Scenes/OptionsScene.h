#include "SceneManager2D.h"
#include "../SoundManager.h"

class OptionsScene : public CSceneManager2D
{
public:

	enum GEOMETRY_TYPE
	{
		GEO_SPLASH,
		NUM_GEOMETRY,
	};

	OptionsScene();
	OptionsScene(int m_window_width, int m_window_height);
	~OptionsScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	Mesh* meshList[NUM_GEOMETRY];

};