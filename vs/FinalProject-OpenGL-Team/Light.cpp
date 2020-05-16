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
		-0.5, -0.5, 0.5, // 0
		 0.5, -0.5, 0.5, // 1
		 0.5,  0.5, 0.5, // 2
		-0.5,  0.5, 0.5, // 3

		// right
		0.5,  0.5,  0.5, // 4
		0.5,  0.5, -0.5, // 5
		0.5, -0.5, -0.5, // 6
		0.5, -0.5,  0.5, // 7

		// back
		-0.5, -0.5, -0.5, // 8 
		 0.5, -0.5, -0.5, // 9
		 0.5,  0.5, -0.5, // 10
		-0.5,  0.5, -0.5, // 11

		// left
		-0.5, -0.5, -0.5, // 12
		-0.5, -0.5,  0.5, // 13
		-0.5,  0.5,  0.5, // 14
		-0.5,  0.5, -0.5, // 15

		// upper
		 0.5, 0.5,  0.5, // 16
		-0.5, 0.5,  0.5, // 17
		-0.5, 0.5, -0.5, // 18
		 0.5, 0.5, -0.5, // 19

		// bottom
		-0.5, -0.5, -0.5, // 20
		 0.5, -0.5, -0.5, // 21
		 0.5, -0.5,  0.5, // 22
		-0.5, -0.5,  0.5, // 23
	};

	unsigned int indices[] = {
		8,  9,  10, 8,  10, 11,  // back
		20, 22, 21, 20, 23, 22,   // bottom
		4,  5,  6,  4,  6,  7,   // right
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		0,  1,  2,  0,  2,  3   // front

	};

	object.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices), false, false);
	object.VerticesDraw(sizeof(indices));

	object.transform.Scale(glm::vec3(0.1f, 0.1f,0.1f));
	object.transform.Rotate(glm::vec3(1, 1, 1), 90);
	object.transform.SetPosition(glm::vec3(1, 1, -2));
}

void Light::Translate(glm::vec3 direction) {
	object.transform.Translate(direction);
}

Transform Light::GetTransform() {
	return object.transform;
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