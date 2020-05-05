#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::SetDefault(bool flag) {
	defaultCamera = flag;
}

void Camera::RenderCamera(GLfloat width, GLfloat height) {
	// Pass perspective projection matrix
	if (defaultCamera) {
		projection = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
	}
	else {
		GLfloat aspect = width / height;
		GLfloat camHeight = 5.0f;
		projection = glm::ortho(-aspect * camHeight / 2.0f, aspect * camHeight / 2.0f, -camHeight / 2.0f, camHeight / 2.0f, 1000.0f, -1000.0f);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// LookAt camera (position, target/direction, up)
	view = glm::lookAt(glm::vec3(2.0f, -1.3f, 2.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));

}