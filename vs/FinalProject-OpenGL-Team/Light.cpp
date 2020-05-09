#include "Light.h"

Light::Light() {
	object = Object3D();
}

Light::~Light() {

}

void Light::CreateLight() {
	object.CreateObject("lightVertex.vert", "lightFragment.frag");

	float vertices[] = {
		// format position, tex coords
		// front
		-0.1, -0.1, 0.1,  // 0
		0.1, -0.1, 0.1,   // 1
		0.1,  0.1, 0.1,   // 2
		-0.1,  0.1, 0.1,  // 3

		// right
		0.1,  0.1,  0.1,  // 4
		0.1,  0.1, -0.1,  // 5
		0.1, -0.1, -0.1,  // 6
		0.1, -0.1,  0.1,  // 7

		// back
		-0.1, -0.1, -0.1, // 8 
		0.1,  -0.1, -0.1, // 9
		0.1,   0.1, -0.1, // 10
		-0.1,  0.1, -0.1, // 11

		// left
		-0.1, -0.1, -0.1, // 12
		-0.1, -0.1,  0.1, // 13
		-0.1,  0.1,  0.1, // 14
		-0.1,  0.1, -0.1, // 15

		// upper
		0.1, 0.1,  0.1,   // 16
		-0.1, 0.1,  0.1,  // 17
		-0.1, 0.1, -0.1,  // 18
		0.1, 0.1, -0.1,   // 19

		// bottom
		-0.1, -0.1, -0.1, // 20
		0.1, -0.1, -0.1,  // 21
		0.1, -0.1,  0.1,  // 22
		-0.1, -0.1,  0.1, // 23
	};

	unsigned int indices[] = {
		8,  9,  10, 8,  10, 11,  // back
		20, 22, 21, 20, 23, 22,   // bottom
		4,  5,  6,  4,  6,  7,   // right
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		0,  1,  2,  0,  2,  3   // front

	};

	object.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices), false);
	object.VerticesDraw(sizeof(indices));

	object.transform.Scale(glm::vec3(0.5f, 0.5f,0.5f));
	object.transform.Rotate(glm::vec3(1, 1, 1), 90);
}

void Light::SetColorLight(glm::vec3 color) {
	lightColor = color;
	object.UseShader();
	glUniform3f(glGetUniformLocation(object.GetShader(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
}

void Light::Render() {
	object.Render();
}

glm::vec3 Light::GetColor() {
	return lightColor;
}

GLuint Light::GetShader() {
	return object.GetShader();
}

void Light::UseShader() {
	object.UseShader();
}