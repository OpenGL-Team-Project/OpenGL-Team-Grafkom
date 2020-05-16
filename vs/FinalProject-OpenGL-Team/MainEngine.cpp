#include "MainEngine.h"



MainEngine::MainEngine() {

}


MainEngine::~MainEngine() {
}

float vertices[] = {
	// format position, tex coords
	// front
	-0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 0, 0,  // 0
	 0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 1, 0,   // 1
	 0.5,  0.5, 0.5, 0.0, 0.0, 1.0, 1, 1,   // 2
	-0.5,  0.5, 0.5, 0.0, 0.0, 1.0, 0, 1,  // 3

	// right
	0.5,  0.5,  0.5, 1.0, 0.0, 0.0, 0, 0,  // 4
	0.5,  0.5, -0.5, 1.0, 0.0, 0.0, 1, 0,  // 5
	0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 1, 1,  // 6
	0.5, -0.5,  0.5, 1.0, 0.0, 0.0, 0, 1,  // 7

	// back
	-0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 0, 0, // 8 
	 0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 1, 0, // 9
	 0.5,  0.5, -0.5, 0.0, 0.0, -1.0, 1, 1, // 10
	-0.5,  0.5, -0.5, 0.0, 0.0, -1.0, 0, 1, // 11

	// left
	-0.5, -0.5, -0.5, -1.0, 0.0, 0.0, 0, 0, // 12
	-0.5, -0.5,  0.5, -1.0, 0.0, 0.0, 1, 0, // 13
	-0.5,  0.5,  0.5, -1.0, 0.0, 0.0, 1, 1, // 14
	-0.5,  0.5, -0.5, -1.0, 0.0, 0.0, 0, 1, // 15

	// upper
	 0.5, 0.5,  0.5, 0.0, 1.0, 0.0, 0, 0,   // 16
	-0.5, 0.5,  0.5, 0.0, 1.0, 0.0, 1, 0,  // 17
	-0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 1, 1,  // 18
	 0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 0, 1,   // 19

	// bottom
	-0.5, -0.5, -0.5, 0.0, -1.0, 0.0, 0, 0, // 20
	 0.5, -0.5, -0.5, 0.0, -1.0, 0.0, 1, 0,  // 21
	 0.5, -0.5,  0.5, 0.0, -1.0, 0.0, 1, 1,  // 22
	-0.5, -0.5,  0.5, 0.0, -1.0, 0.0, 0, 1, // 23
};

unsigned int indices[] = {
	8,  9,  10, 8,  10, 11,  // back
	20, 22, 21, 20, 23, 22,   // bottom
	4,  5,  6,  4,  6,  7,   // right
	12, 14, 13, 12, 15, 14,  // left
	16, 18, 17, 16, 19, 18,  // upper
	0,  1,  2,  0,  2,  3   // front

};

void MainEngine::Init() {
	// build and compile our shader program
	// ------------------------------------
	control = Control();
	camera = Camera();
	plane = Object3D();
	cube = Object3D();
	light = Light();

	//skyIsland
	soil = Object3D();
	soil1 = Object3D();
	soil2 = Object3D();
	soil3 = Object3D();
	soil4 = Object3D();
	soil5 = Object3D();
	soil6 = Object3D();
	tower = Object3D();
	slab = Object3D();
	slab1 = Object3D();
	slab2 = Object3D();
	slab3 = Object3D();
	tree1 = Object3D();
	tree2 = Object3D();
	tree3 = Object3D();
	leaf1 = Object3D();
	leaf2 = Object3D();
	leaf3 = Object3D();

	camera.SetDefault(false);

	BuildLight();
	BuildCube();

	//skyIsland
	BuildSoil();
	BuildSoil1();
	BuildSoil2();
	BuildSoil3();
	BuildSoil4();
	BuildSoil5();
	BuildSoil6();
	BuildTower();
	BuildSlab();
	BuildSlab1();
	BuildSlab2();
	BuildSlab3();
	BuildTree1();
	BuildTree2();
	BuildTree3();
	BuildLeaf1();
	BuildLeaf2();
	BuildLeaf3();
}

void MainEngine::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	cube.DeInit();
	plane.DeInit();

	soil.DeInit();
	soil1.DeInit();
	soil2.DeInit();
	soil3.DeInit();
	soil4.DeInit();
	soil5.DeInit();
	soil6.DeInit();
	tower.DeInit();
	slab.DeInit();
	slab1.DeInit();
	slab2.DeInit();
	slab3.DeInit();
	tree1.DeInit();
	tree2.DeInit();
	tree3.DeInit();
	leaf1.DeInit();
	leaf2.DeInit();
	leaf3.DeInit();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void MainEngine::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	control.vk_left = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
	control.vk_up = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
	control.vk_right = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
	control.vk_down = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
}

void MainEngine::Update(double deltaTime) {
	if (control.vk_left) {
		camera.Orbit(-0.1f * deltaTime);
	} else if (control.vk_right) {
		camera.Orbit(0.1f * deltaTime);
	}
	
	if (control.vk_up) {
		camera.Zoom(-0.02f *deltaTime);
	}
	else if (control.vk_down) {
		camera.Zoom(0.02f * deltaTime);
	}


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		light.Translate(glm::vec3(0, 0, 1 * deltaTime * 0.001f));
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		light.Translate(glm::vec3(0, 0, -1 * deltaTime * 0.001f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		light.Translate(glm::vec3(-1 * deltaTime * 0.001f, 0, 0));
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		light.Translate(glm::vec3(1 * deltaTime * 0.001f, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		light.Translate(glm::vec3(0, -1 * deltaTime * 0.001f, 0));
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		light.Translate(glm::vec3(0, 1 * deltaTime * 0.001f, 0));
	}
}

void MainEngine::DrawObject() {
	camera.RenderCamera(this->screenWidth, this->screenHeight);	

	//Projection the object here
	//light
	light.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(light.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(light.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	light.Render();

	//cube
	//cube.UseShader();
	//glUniformMatrix4fv(glGetUniformLocation(cube.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	//glUniformMatrix4fv(glGetUniformLocation(cube.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	//glUniform3f(glGetUniformLocation(cube.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	//cube.Render();

	//SkyIsland
	//soil
	soil.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(soil.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(soil.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(soil.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(soil.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(soil.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * soil.transform.model)))));
	glUniform3f(glGetUniformLocation(soil.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);

	soil.Render();

	//soil1
	soil1.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(soil1.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(soil1.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(soil1.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(soil1.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(soil1.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * soil1.transform.model)))));
	glUniform3f(glGetUniformLocation(soil1.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	soil1.Render();

	//soil2
	soil2.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(soil2.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(soil2.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(soil2.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(soil2.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(soil2.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * soil2.transform.model)))));
	glUniform3f(glGetUniformLocation(soil2.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	soil2.Render();

	//soil3
	soil3.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(soil3.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(soil3.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(soil3.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(soil3.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(soil3.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * soil3.transform.model)))));
	glUniform3f(glGetUniformLocation(soil3.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	soil3.Render();

	//soil4
	soil4.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(soil4.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(soil4.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(soil4.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(soil4.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(soil4.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * soil4.transform.model)))));
	glUniform3f(glGetUniformLocation(soil4.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	soil4.Render();

	//soil5
	soil5.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(soil5.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(soil5.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(soil5.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(soil5.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(soil5.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * soil5.transform.model)))));
	glUniform3f(glGetUniformLocation(soil5.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	soil5.Render();

	//soil6
	soil6.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(soil6.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(soil6.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(soil6.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(soil6.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(soil6.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * soil6.transform.model)))));
	glUniform3f(glGetUniformLocation(soil6.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	soil6.Render();

	//tower
	tower.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(tower.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(tower.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(tower.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(tower.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(tower.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view * tower.transform.model)))));
	glUniform3f(glGetUniformLocation(tower.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	tower.Render();

	//slab
	slab.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(slab.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(slab.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(slab.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(slab.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(slab.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* slab.transform.model)))));
	glUniform3f(glGetUniformLocation(slab.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	slab.Render();

	//slab1
	slab1.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(slab1.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(slab1.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(slab1.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(slab1.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(slab1.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* slab1.transform.model)))));
	glUniform3f(glGetUniformLocation(slab1.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	slab1.Render();

	//slab2
	slab2.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(slab2.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(slab2.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(slab2.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(slab2.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(slab2.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* slab2.transform.model)))));
	glUniform3f(glGetUniformLocation(slab2.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	slab2.Render();

	//slab3
	slab3.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(slab3.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(slab3.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(slab3.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(slab3.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(slab3.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* slab3.transform.model)))));
	glUniform3f(glGetUniformLocation(slab3.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	slab3.Render();

	//tree1
	tree1.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(tree1.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(tree1.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(tree1.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(tree1.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(tree1.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* tree1.transform.model)))));
	glUniform3f(glGetUniformLocation(tree1.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	tree1.Render();

	//tree2
	tree2.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(tree2.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(tree2.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(tree2.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(tree2.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(tree2.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* tree2.transform.model)))));
	glUniform3f(glGetUniformLocation(tree2.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	tree2.Render();

	//tree3
	tree3.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(tree3.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(tree3.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(tree3.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(tree3.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(tree3.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* tree3.transform.model)))));
	glUniform3f(glGetUniformLocation(tree3.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	tree3.Render();

	//leaf1
	leaf1.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(leaf1.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(leaf1.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(leaf1.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(leaf1.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(leaf1.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* leaf1.transform.model )))));
	glUniform3f(glGetUniformLocation(leaf1.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	leaf1.Render();

	//leaf2
	leaf2.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(leaf2.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(leaf2.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(leaf2.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(leaf2.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(leaf2.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* leaf2.transform.model)))));
	glUniform3f(glGetUniformLocation(leaf2.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	leaf2.Render();

	//leaf3
	leaf3.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(leaf3.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(leaf3.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniform3f(glGetUniformLocation(leaf3.GetShader(), "lightColor"), light.GetColor().x, light.GetColor().y, light.GetColor().z);
	glUniform3f(glGetUniformLocation(leaf3.GetShader(), "lightPos"), light.GetTransform().position.x, light.GetTransform().position.y, light.GetTransform().position.z);
	glUniformMatrix3fv(glGetUniformLocation(leaf3.GetShader(), "inverse"), 1, GL_FALSE, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(camera.view* leaf3.transform.model)))));
	glUniform3f(glGetUniformLocation(leaf3.GetShader(), "viewPos"), camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	leaf3.Render();
}

void MainEngine::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	DrawObject();
	   
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

}

void MainEngine::BuildLight() {
	light.CreateLight();
	light.SetColorLight(glm::vec3(1.0f, 1.0f, 1.0f));
	
}

void MainEngine::BuildCube() {
	
	cube.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	cube.BuildObject(vertices, sizeof(vertices) , indices, sizeof(indices));
	cube.VerticesDraw(sizeof(indices));
	cube.ApplyTexture("diamond_ore.png");
	cube.transform.SetOrigin( glm::vec3(0.0f, 0.0f, 0.0f));
	cube.transform.SetPosition(glm::vec3(-2.0f, -0.4f, -0.4f));
}

void MainEngine::BuildSoil() {
	soil.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	soil.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	soil.VerticesDraw(sizeof(indices));
	soil.ApplyTexture("soil.png");
	soil.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	soil.transform.Scale(glm::vec3(1.0f, 0.15f, 1.3f));
	soil.transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void MainEngine::BuildSoil1() {
	soil1.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	soil1.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	soil1.VerticesDraw(sizeof(indices));
	soil1.ApplyTexture("soil.png");
	soil1.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	soil1.transform.Scale(glm::vec3(1.3f, 0.15f, 1.0f));
	soil1.transform.SetPosition(glm::vec3(0.0f, 0.0f, -0.1f));
}

void MainEngine::BuildSoil2() {
	soil2.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	soil2.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	soil2.VerticesDraw(sizeof(indices));
	soil2.ApplyTexture("soil.png");
	soil2.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	soil2.transform.Scale(glm::vec3(0.5f, -1.0f, 0.5f));
	soil2.transform.SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));
}

void MainEngine::BuildSoil3() {
	soil3.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	soil3.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	soil3.VerticesDraw(sizeof(indices));
	soil3.ApplyTexture("soil.png");
	soil3.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	soil3.transform.Scale(glm::vec3(0.5f, -0.9f, 0.5f));
	soil3.transform.SetPosition(glm::vec3(0.3f, -0.45f, 0.3f));
}

void MainEngine::BuildSoil4() {
	soil4.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	soil4.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	soil4.VerticesDraw(sizeof(indices));
	soil4.ApplyTexture("soil.png");
	soil4.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	soil4.transform.Scale(glm::vec3(0.5f, -0.85f, 0.5f));
	soil4.transform.SetPosition(glm::vec3(-0.25f, -0.425f, -0.25f));
}

void MainEngine::BuildSoil5() {
	soil5.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	soil5.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	soil5.VerticesDraw(sizeof(indices));
	soil5.ApplyTexture("soil.png");
	soil5.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	soil5.transform.Scale(glm::vec3(0.5f, -0.7f, 0.5f));
	soil5.transform.SetPosition(glm::vec3(-0.25f, -0.35f, 0.25f));
}

void MainEngine::BuildSoil6() {
	soil6.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	soil6.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	soil6.VerticesDraw(sizeof(indices));
	soil6.ApplyTexture("soil.png");
	soil6.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	soil6.transform.Scale(glm::vec3(0.5f, -0.7f, 0.5f));
	soil6.transform.SetPosition(glm::vec3(0.25f, -0.35f, -0.25f));
}

void MainEngine::BuildTower() {
	tower.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	tower.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	tower.VerticesDraw(sizeof(indices));
	tower.ApplyTexture("tower.png");
	tower.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	tower.transform.Scale(glm::vec3(0.6f, 1.1f, 0.6f));
	tower.transform.SetPosition(glm::vec3(0.0f, 0.55f, 0.2f));
}

void MainEngine::BuildSlab() {
	slab.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	slab.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	slab.VerticesDraw(sizeof(indices));
	slab.ApplyTexture("slab.png");
	slab.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	slab.transform.Scale(glm::vec3(0.8f, 0.1f, 0.8f));
	slab.transform.SetPosition(glm::vec3(0.0f, 0.8f, 0.2f));
}

void MainEngine::BuildSlab1() {
	slab1.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	slab1.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	slab1.VerticesDraw(sizeof(indices));
	slab1.ApplyTexture("slab.png");
	slab1.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	slab1.transform.Scale(glm::vec3(0.3f, 0.1f, 0.1f));
	slab1.transform.SetPosition(glm::vec3(0.0f, 0.4f, -0.15f));
}

void MainEngine::BuildSlab2() {
	slab2.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	slab2.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	slab2.VerticesDraw(sizeof(indices));
	slab2.ApplyTexture("slab.png");
	slab2.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	slab2.transform.Scale(glm::vec3(0.1f, 0.35f, 0.1f));
	slab2.transform.SetPosition(glm::vec3(-0.1f, 0.175f, -0.15f));
}

void MainEngine::BuildSlab3() {
	slab3.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	slab3.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	slab3.VerticesDraw(sizeof(indices));
	slab3.ApplyTexture("slab.png");
	slab3.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	slab3.transform.Scale(glm::vec3(0.1f, 0.35f, 0.1f));
	slab3.transform.SetPosition(glm::vec3(0.1f, 0.175f, -0.15f));
}

void MainEngine::BuildTree1() {
	tree1.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	tree1.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	tree1.VerticesDraw(sizeof(indices));
	tree1.ApplyTexture("tree.png");
	tree1.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	tree1.transform.Scale(glm::vec3(0.1f, 0.35f, 0.1f));
	tree1.transform.SetPosition(glm::vec3(-0.4f, 0.175f, -0.4f));
}

void MainEngine::BuildTree2() {
	tree2.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	tree2.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	tree2.VerticesDraw(sizeof(indices));
	tree2.ApplyTexture("tree.png");
	tree2.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	tree2.transform.Scale(glm::vec3(0.1f, 0.35f, 0.1f));
	tree2.transform.SetPosition(glm::vec3(0.5f, 0.175f, -0.3f));
}

void MainEngine::BuildTree3() {
	tree3.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	tree3.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	tree3.VerticesDraw(sizeof(indices));
	tree3.ApplyTexture("tree.png");
	tree3.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	tree3.transform.Scale(glm::vec3(0.1f, 0.35f, 0.1f));
	tree3.transform.SetPosition(glm::vec3(-0.35f, 0.175f, 0.25f));
}

void MainEngine::BuildLeaf1() {
	leaf1.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	leaf1.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	leaf1.VerticesDraw(sizeof(indices));
	leaf1.ApplyTexture("leaf.png");
	leaf1.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	leaf1.transform.Scale(glm::vec3(0.3f, 0.3f, 0.3f));
	leaf1.transform.SetPosition(glm::vec3(-0.4f, 0.4f, -0.4f));
}

void MainEngine::BuildLeaf2() {
	leaf2.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	leaf2.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	leaf2.VerticesDraw(sizeof(indices));
	leaf2.ApplyTexture("leaf.png");
	leaf2.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	leaf2.transform.Scale(glm::vec3(0.3f, 0.2f, 0.3f));
	leaf2.transform.SetPosition(glm::vec3(0.5f, 0.3f, -0.3f));
}

void MainEngine::BuildLeaf3() {
	leaf3.CreateObject("vertexShader.vert", "fragmentShader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	leaf3.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	leaf3.VerticesDraw(sizeof(indices));
	leaf3.ApplyTexture("leaf.png");
	leaf3.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	leaf3.transform.Scale(glm::vec3(0.3f, 0.2f, 0.3f));
	leaf3.transform.SetPosition(glm::vec3(-0.35f, 0.3f, 0.25f));
}

int main(int argc, char** argv) {
	MainEngine engine = MainEngine();
	RenderEngine& app = engine;
	app.Start("Blending Demo", 800, 600, false, false);
}