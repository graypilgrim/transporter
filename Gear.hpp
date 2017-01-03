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
		size_t index = 0;
		GLfloat zValue = -2.0f;
		CreateCircles(index, zValue);
		CreateSides(index, zValue);

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
	void CreateCircles(size_t &index, GLfloat height) {
		GLfloat zValue = 0.0f;
		CreateCircle(index, zValue);

		std::cout << index << std::endl;

		zValue = height;
		CreateCircle(index, zValue);

		std::cout << index << std::endl;
	}

	void CreateCircle(size_t &index, GLfloat zValue) {
		for (size_t i = 0; i < segmentsNo; ++i) {
			vertices[index] = 0.0f;
			vertices[index + 1] = 0.0f;
			vertices[index + 2] = zValue;

			vertices[index + 3] = vertices[index + 12] = radius * cos(i * circleQuantum);
			vertices[index + 4] = vertices[index + 13] = radius * sin(i * circleQuantum);
			vertices[index + 5] = vertices[index + 14] = zValue;

			vertices[index + 6] = vertices[index + 15] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 7] = vertices[index + 16] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 8] = vertices[index + 17] = zValue;

			vertices[index + 9] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 10] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 11] = zValue;

			index += 18;
		}
	}

	void CreateSides(size_t &index, GLfloat zValue) {
		for (size_t i = 0; i < segmentsNo; ++i) {
			vertices[index] = radius * cos(i * circleQuantum);
			vertices[index + 1] = radius * sin(i * circleQuantum);
			vertices[index + 2] = 0.0f;

			vertices[index + 3] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 4] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 5] = 0.0f;

			vertices[index + 6] = radius * cos(i * circleQuantum);
			vertices[index + 7] = radius * sin(i * circleQuantum);
			vertices[index + 8] = zValue;

			vertices[index + 9] = radius * cos(i * circleQuantum);
			vertices[index + 10] = radius * sin(i * circleQuantum);
			vertices[index + 11] = zValue;

			vertices[index + 12] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 13] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 14] = zValue;

			vertices[index + 15] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 16] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 17] = 0.0f;

			vertices[index + 18] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 19] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 20] = 0.0f;

			vertices[index + 21] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 22] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 23] = 0.0f;

			vertices[index + 24] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 25] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 26] = zValue;

			vertices[index + 27] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 28] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 29] = zValue;

			vertices[index + 30] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 31] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 32] = zValue;

			vertices[index + 33] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 34] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 35] = 0.0f;

			index += 36;
		}
	}

	const size_t verticeCoordNo = 3;
	const GLfloat radius = 1.0f;

	const size_t segmentsNo;
	const size_t verticesNo = 24 * segmentsNo;
	const GLfloat circleQuantum = 2 * M_PI/segmentsNo;

	GLuint VBO;
	GLuint VAO;

	GLfloat *vertices;
};

#endif
