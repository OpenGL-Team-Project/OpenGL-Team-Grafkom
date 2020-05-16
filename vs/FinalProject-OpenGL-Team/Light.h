#ifndef LIGHT_H
#define LIGHT_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Object3D.h"

class Light {
public:
	Light();
	~Light();
	void CreateLight();
	void SetColorLight(glm::vec3 color);
	void Render();
	glm::vec3 GetColor();
	GLuint GetShader();
	void UseShader();
	void Translate(glm::vec3 direction);
	Transform GetTransform();
private:
	glm::vec3 lightColor;
	Object3D object;
};

#endif
