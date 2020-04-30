#include "MainEngine.h"



MainEngine::MainEngine() {

}


MainEngine::~MainEngine() {
}


void MainEngine::Init() {
	// build and compile our shader program
	// ------------------------------------
	shader = Shader("vertexShader.vert", "fragmentShader.frag");
	plane = Object3D();
	cube = Object3D();

	BuildCube();

}

void MainEngine::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	cube.DeInit();
	plane.DeInit();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void MainEngine::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void MainEngine::Update(double deltaTime) {

}

void MainEngine::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Pass perspective projection matrix
	bool useDefaultCamera = false;
	glm::mat4 projection;
	if (useDefaultCamera) {
		glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	}
	else {
		GLfloat aspect = (GLfloat)this->screenWidth / (GLfloat)this->screenHeight;
		GLfloat camHeight = 5.0f;
		glm::mat4 projection = glm::ortho(-aspect * camHeight / 2.0f, aspect * camHeight / 2.0f, -camHeight / 2.0f, camHeight / 2.0f, 1000.0f, -1000.0f);
	}
	GLint projLoc = glGetUniformLocation(this->shader.GetShader(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(2.0f, -1.3f, 2.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
	GLint viewLoc = glGetUniformLocation(this->shader.GetShader(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	DrawCube();



	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

}

void MainEngine::BuildCube() {
	
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
	cube.SetShader(shader);
	cube.VerticesDraw(sizeof(indices));
	cube.ApplyTexture("diamond_ore.png");
}

void MainEngine::DrawCube()
{
	cube.Render();
}


int main(int argc, char** argv) {
	MainEngine engine = MainEngine();
	RenderEngine& app = engine;
	app.Start("Blending Demo", 800, 600, false, false);
}