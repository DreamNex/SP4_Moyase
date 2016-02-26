#include "SceneManager2D.h"
#include "../UI/SliderUI.h"
#include <vector>

class OptionsScene : public CSceneManager2D
{
public:

	enum GEOMETRY_TYPE
	{
		GEO_SPLASH,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	OptionsScene();
	OptionsScene(int m_window_width, int m_window_height);
	~OptionsScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	std::vector<SliderUI*> Sliders;

private:
	Mesh* meshList[NUM_GEOMETRY];
};