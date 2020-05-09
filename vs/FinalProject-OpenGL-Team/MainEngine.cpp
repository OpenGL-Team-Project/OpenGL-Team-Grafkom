#include "MainEngine.h"



MainEngine::MainEngine() {

}


MainEngine::~MainEngine() {
}


void MainEngine::Init() {
	// build and compile our shader program
	// ------------------------------------
	camera = Camera();
	plane = Object3D();
	cube = Object3D();
	block = Object3D();

	camera.SetDefault(false);

	

	BuildCube();
	BuildBlock();

}

void MainEngine::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	cube.DeInit();
	block.DeInit();
	plane.DeInit();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void MainEngine::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void MainEngine::Update(double deltaTime) {
	camera.Movement(0.01f * deltaTime);

	cube.transform.Rotate(glm::vec3(0.0f, 0.0f, 1.0f), (float)glfwGetTime() * 10);
	block.transform.Rotate(glm::vec3(0.0f, 0.0f, 1.0f), (float)glfwGetTime() * 30);
}

void MainEngine::DrawObject() {
	camera.RenderCamera(this->screenWidth, this->screenHeight);

	//Projection the object here
	//cube
	glUniformMatrix4fv(glGetUniformLocation(cube.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(cube.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	cube.Render();
	

	//block
	glUniformMatrix4fv(glGetUniformLocation(block.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(block.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	block.Render();
}

void MainEngine::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	DrawObject();
	   
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

}

void MainEngine::BuildCube() {
	
	cube.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		8,  9,  10, 8,  10, 11,  // back
		20, 22, 21, 20, 23, 22,   // bottom
		4,  5,  6,  4,  6,  7,   // right
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		0,  1,  2,  0,  2,  3   // front

	};


	cube.BuildObject(vertices, sizeof(vertices) , indices, sizeof(indices));
	cube.VerticesDraw(sizeof(indices));
	cube.ApplyTexture("diamond_ore.png");
	cube.transform.SetOrigin( glm::vec3(0.0f, 0.0f, 0.0f));
	cube.transform.SetPosition(glm::vec3(-2.0f, -0.4f, -0.4f));
}

void MainEngine::BuildBlock() {

	block.CreateObject("vertexShader.vert", "fragmentShader.frag");

	float vertices[] = {
		// format position, tex coords
		// front
		-0.125, -0.5, 0.25, 0, 0, //0
		0.125, -0.5, 0.25, 1, 0, //1
		0.125, 0.5, 0.25, 1, 1, //2
		-0.125, 0.5, 0.25, 0, 1, //3

		// right
		0.125, 0.5, 0.25, 0, 0, //4
		0.125, 0.5, -0.25  , 1, 0, //5
		0.125, -0.5, -0.25  , 1, 1, //6
		0.125, -0.5, 0.25, 0, 1, //7

		// back
		-0.125, -0.5, -0.25, 0, 0, //8
		0.125, -0.5, -0.25, 1, 0, //9
		0.125, 0.5, -0.25, 1, 1, //10
		-0.125, 0.5, -0.25, 0, 1, //11

		// left
		-0.125, -0.5, -0.25,   0, 0, //12
		-0.125, -0.5, 0.25, 1, 0, //13
		-0.125, 0.5, 0.25, 1, 1, //14
		-0.125, 0.5, -0.25,   0, 1, //15

		// upper
		0.125, 0.5, 0.25, 0, 0, //16
		-0.125, 0.5, 0.25, 1, 0, //17
		-0.125, 0.5, -0.25,   1, 1, //18
		0.125, 0.5, -0.25,   0, 1, //19

		// bottom
		-0.125, -0.5, -0.25, 0, 0, //20
		0.125, -0.5, -0.25, 1, 0, //21
		0.125, -0.5, 0.25,   1, 1, //22
		-0.125, -0.5, 0.25,   0, 1, //23

	};

	unsigned int indices[] = {
		8,  9,  10, 8,  10, 11,  // back
		20, 22, 21, 20, 23, 22,   // bottom
		4,  5,  6,  4,  6,  7,   // right
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		0,  1,  2,  0,  2,  3   // front
	};

	block.BuildObject(vertices, sizeof(vertices) , indices, sizeof(indices));
	block.VerticesDraw(sizeof(indices));
	block.ApplyTexture("dirt.png");

	block.transform.SetPosition(glm::vec3(2.0f, 0.4f, 0.4f));
	block.transform.SetOrigin(glm::vec3(0.0f, 0.5f, 0.5f));
}


int main(int argc, char** argv) {
	MainEngine engine = MainEngine();
	RenderEngine& app = engine;
	app.Start("Blending Demo", 800, 600, false, false);
}