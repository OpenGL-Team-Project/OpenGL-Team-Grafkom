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
#include "Control.h"
#include "Light.h"

class MainEngine :
	public RenderEngine
{
public:
	MainEngine();
	~MainEngine();
	Object3D cube;
	Object3D plane;
	Object3D soil;
	Object3D soil1;
	Object3D soil2;
	Object3D soil3;
	Object3D soil4;
	Object3D soil5;
	Object3D soil6;

	Object3D tower;
	
	Object3D slab;
	Object3D slab1;
	Object3D slab2;
	Object3D slab3;
	
	Object3D tree1;
	Object3D tree2;
	Object3D tree3;

	Object3D leaf1;
	Object3D leaf2;
	Object3D leaf3;
	Light light;
	Shader depthmapShader, shadowmapShader;
	GLuint depthMapFBO, depthMap;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

private:
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void BuildCube();
	void DrawObject();
	void BuildLight();
	void BuildSoil();
	void BuildSoil1();
	void BuildSoil2();
	void BuildSoil3();
	void BuildSoil4();
	void BuildSoil5();
	void BuildSoil6();
	void BuildTower();
	void BuildSlab();
	void BuildSlab1();
	void BuildSlab2();
	void BuildSlab3();
	void BuildTree1();
	void BuildTree2();
	void BuildTree3();
	void BuildLeaf1();
	void BuildLeaf2();
	void BuildLeaf3();
	void BuildDepthMap();
	void BuildShaders();
	Camera camera;
	Control control;
};

