#include "Object3D.h"

Object3D::Object3D(){
	transform = Transform();
	shader = Shader();
}

Object3D::~Object3D(){

}

void Object3D::DeInit() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Object3D::CreateObject(const char* vertexPath, const char* fragmentPath) {
	shader.BuildShader(vertexPath, fragmentPath);
}

void Object3D::CreateObjectShader(Shader shader) {
	this->shader = shader;
}

//This Method is for default vertex shader
//vertices must include vec3 position and vec2 texCoord
void Object3D::BuildObject(float* _vertices, size_t verticesSize, unsigned int* _indices, size_t indicesSize, bool faces_defined, bool using_texture) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, _vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, _indices, GL_STATIC_DRAW);

	

	textureEnabled = using_texture;
	if (faces_defined && textureEnabled) {
		// define position pointer layout 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);

		// define position pointer layout 1
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);

		// define texcoord pointer layout 2
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	else if (faces_defined) {
		// define position pointer layout 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);

		// define position pointer layout 1
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
	}
	else {
		// define position pointer layout 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
	}

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object3D::SetShader(Shader shader) {
	this->shader = shader;
}

GLuint Object3D::GetShader() {
	return shader.GetShader();
}

void Object3D::VerticesDraw(int verticesDraw) {
	this->verticesDraw = verticesDraw;
}
	
GLuint Object3D::GetVAO() {
	return VAO;
}

GLuint Object3D::GetVBO() {
	return VBO;
}
	
GLuint Object3D::GetEBO() {
	return EBO;
}

void Object3D::Render() {
	shader.Use();

	transform.Execute(shader);

	if (textureEnabled) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glUniform1i(glGetUniformLocation(shader.GetShader(), "ourTexture"), 0);
	}

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, verticesDraw, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, verticesDraw);

	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	//shader.UnUse();

}

void Object3D::ApplyTexture(const char* _texturePath) {
	if (textureEnabled) {
		// load image into texture memory
		// ------------------------------
		// Load and create a texture 
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width, height;
		unsigned char* image = SOIL_load_image(_texturePath, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		std::cout << "This object is not using Texture when build. \n" << std::endl;
	}
}

void Object3D::UseShader() {
	shader.Use();
}