#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>
#include "Shader.h"
#include "Object3D.h"
#include "Camera.h"

class MainEngine :
	public RenderEngine
{
public:
	MainEngine();
	~MainEngine();
	Object3D cube;
	Object3D plane;
	Object3D block;
private:
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void BuildCube();
	void BuildBlock();
	void DrawObject();
	Camera camera;
};

