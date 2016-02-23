#ifndef SCENE_MANAGER2D_H
#define SCENE_MANAGER2D_H

#include "Scene.h"
#include "Mtx44.h"
#include "../Camera3.h"
#include "../Mesh.h"
#include "MatrixStack.h"
#include "../Light.h"

const float SKYBOXSIZE2D = 1000.f;

class CSceneManager2D : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_LIGHTENABLED,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:

	CSceneManager2D(void);
	CSceneManager2D(const int m_window_width, const int m_window_height);
	~CSceneManager2D(void);

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	// Low level render tools
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z = 0);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float sizeX = 1.0f, float sizeY = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0, float rotate = 0, float centerOffsetX = 0, float centerOffsetY = 0);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void Render2DMesh(Mesh *mesh, float scaleX = 1.f, float scaleY = 1.f, float x = 0, float y = 0, float rotate = 0, float centerOffsetX = 0, float centerOffsetY = 0);

protected:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	// Handler to the camera
	Camera3 camera;

	// Rotation angle for use with the model stack
	float rotateAngle;

	// Matrices for Model, View and Projection stack
	MS modelStack;
	MS viewStack;
	MS projectionStack;

	// Window size
	int m_window_width;
	int m_window_height;

	float fps;
};

#endif