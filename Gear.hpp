#ifndef GEAR_HPP
#define GEAR_HPP

#include <GL/glew.h>
#include <cstring>
#include <cmath>
#include <iostream>

class Gear
{
public:
	Gear(size_t segments)
	:segmentsNo(segments) {
		vertices = new GLfloat[verticesNo * verticeCoordNo];

		memset(vertices, 0, this->GetArraySize());

		DrawCircles();

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->GetArraySize(), this->GetVertices(), GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);


		glBindVertexArray(0);
	}

	~Gear() {
		delete[] vertices;
	}

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

private:
	void DrawCircles() {
		size_t index = 0;
		GLfloat zValue = 0.0f;

		for (size_t i = 0; i < segmentsNo; ++i) {
			vertices[index] = 0.0f;
			vertices[index + 1] = 0.0f;
			vertices[index + 2] = zValue;

			vertices[index] = radius * cos(i * circleQuantum);
			vertices[index + 1] = radius * sin(i * circleQuantum);
			vertices[index + 2] = zValue;

			vertices[index] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 1] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 2] = zValue;

			index += 6;
		}

		zValue = 2.0f;

		for (size_t i = 0; i < segmentsNo; ++i) {
			vertices[index] = 0.0f;
			vertices[index + 1] = 0.0f;
			vertices[index + 2] = zValue;

			vertices[index] = radius * cos(i * circleQuantum);
			vertices[index + 1] = radius * sin(i * circleQuantum);
			vertices[index + 2] = zValue;

			vertices[index] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 1] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 2] = zValue;

			index += 6;
		}
	}

	const size_t verticeCoordNo = 3;
	const GLfloat radius = 1.0f;
	const GLfloat circleQuantum = 2 * M_PI/segmentsNo;

	const size_t segmentsNo;
	const size_t verticesNo = 24 * segmentsNo;

	GLuint VBO;
	GLuint VAO;

	GLfloat *vertices;
};

#endif
