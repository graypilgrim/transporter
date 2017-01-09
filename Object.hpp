#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include <GL/glew.h>
#include <string.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "Shader.hpp"

class Object
{
public:
	Object(size_t vertices, size_t coordinatesNo)
	:verticesNo(vertices), verticeCoordNo(coordinatesNo)
	{}

	GLfloat *GetVertices() {
		return vertices;
	}

	size_t GetVerticesNo() {
		return verticesNo;
	}

	size_t GetArraySize() {
		return sizeof(GLfloat) * verticesNo * verticeCoordNo;
	}

	GLuint GetVAO() {
		return VAO;
	}

	GLuint GetVBO() {
		return VBO;
	}

	GLuint GetTexture() {
		return texture;
	}

	void SetCamera(Camera *c) {
		camera = c;
	}

	void SetShader(Shader *s) {
		shader = s;
	}

protected:
	void BindVertices() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		    // Bind our Vertex Array Object first, then bind and set our buffers and pointers.
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, GetArraySize(), GetVertices(), GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	const size_t verticesNo;
	const size_t verticeCoordNo;

	GLuint VBO;
	GLuint VAO;
	GLuint texture;

	GLfloat *vertices;

	Camera *camera;
	Shader *shader;
};

#endif
