#include "../headers/Object.hpp"

Object::Object(size_t vertices, size_t coordinatesNo)
:verticesNo(vertices), verticeCoordNo(coordinatesNo)
{}

GLfloat *Object::GetVertices() {
	return vertices;
}

size_t Object::GetVerticesNo() {
	return verticesNo;
}

size_t Object::GetArraySize() {
	return sizeof(GLfloat) * verticesNo * verticeCoordNo;
}

GLuint Object::GetVAO() {
	return VAO;
}

GLuint Object::GetVBO() {
	return VBO;
}

GLuint Object::GetTexture() {
	return texture;
}

void Object::SetCamera(Camera *c) {
	camera = c;
}

void Object::SetShader(Shader *s) {
	shader = s;
}

void Object::BindVertices() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, GetArraySize(), GetVertices(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
