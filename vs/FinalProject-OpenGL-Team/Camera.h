#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
public:
	Camera();
	~Camera();

	glm::mat4 projection;
	glm::mat4 view;

	void SetDefault(bool flag);
	void RenderCamera(GLfloat width, GLfloat height);

private:
	bool defaultCamera = true;
};

#endif