#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	Shader();
	~Shader();
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	GLuint GetShader();
	void Use();
private:
	GLuint shaderProgram;
	void Err(std::string errorString);
	void CheckShaderErrors(GLuint shader, std::string type);
};


#endif 