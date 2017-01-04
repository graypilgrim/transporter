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
		GLfloat zValue = -4.0f;
		CreateCircles(index, zValue);
		CreateSides(index, zValue);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->GetArraySize(), this->GetVertices(), GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

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
		GLfloat normal = zValue == 0.0f ? -1.0f : 1.0f;

		for (size_t i = 0; i < segmentsNo; ++i) {
			vertices[index] = 0.0f;
			vertices[index + 1] = 0.0f;
			vertices[index + 2] = zValue;
			vertices[index + 3] = 0.0f;
			vertices[index + 4] = 0.0f;
			vertices[index + 5] = normal;

			vertices[index + 6] = vertices[index + 12] = radius * cos(i * circleQuantum);
			vertices[index + 7] = vertices[index + 13] = radius * sin(i * circleQuantum);
			vertices[index + 8] = vertices[index + 14] = zValue;
			vertices[index + 9] = 0.0f;
			vertices[index + 10] = 0.0f;
			vertices[index + 11] = normal;
			vertices[index + 15] = 0.0f;
			vertices[index + 16] = 0.0f;
			vertices[index + 17] = normal;

			vertices[index + 18] = vertices[index + 24] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 19] = vertices[index + 25] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 20] = vertices[index + 26] = zValue;
			vertices[index + 21] = 0.0f;
			vertices[index + 22] = 0.0f;
			vertices[index + 23] = normal;
			vertices[index + 27] = 0.0f;
			vertices[index + 28] = 0.0f;
			vertices[index + 29] = normal;

			vertices[index + 30] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 31] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 32] = zValue;
			vertices[index + 33] = 0.0f;
			vertices[index + 34] = 0.0f;
			vertices[index + 35] = normal;

			index += 36;
		}
	}

	void CreateSides(size_t &index, GLfloat zValue) {
		for (size_t i = 0; i < segmentsNo; ++i) {
			//first triangle
			vertices[index] = radius * cos(i * circleQuantum);
			vertices[index + 1] = radius * sin(i * circleQuantum);
			vertices[index + 2] = 0.0f;

			vertices[index + 6] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 7] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 8] = 0.0f;

			vertices[index + 12] = radius * cos(i * circleQuantum);
			vertices[index + 13] = radius * sin(i * circleQuantum);
			vertices[index + 14] = zValue;

			//normal calculation
			GLfloat U[3] = {vertices[index + 6] - vertices[index],
							vertices[index + 7] - vertices[index + 1],
							vertices[index + 8] - vertices[index + 2]};

			GLfloat V[3] = {vertices[index + 12] - vertices[index],
							vertices[index + 13] - vertices[index + 1],
							vertices[index + 14] - vertices[index + 2]};

			GLfloat normal[3];
			normal[0] = U[1] * V[2] - U[2] * V[1];
			normal[1] = U[2] * V[0] - U[0] * U[2];
			normal[2] = U[0] * V[1] - U[1] * V[0];

			vertices[index + 3] = vertices[index + 9] = vertices[index + 15] = normal[0];
			vertices[index + 4] = vertices[index + 10] = vertices[index + 16] = normal[1];
			vertices[index + 5] = vertices[index + 11] = vertices[index + 17] = normal[2];


			vertices[index + 18] = radius * cos(i * circleQuantum);
			vertices[index + 19] = radius * sin(i * circleQuantum);
			vertices[index + 20] = zValue;
			vertices[index + 21] = normal[0];
			vertices[index + 22] = normal[1];
			vertices[index + 23] = normal[2];

			vertices[index + 24] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 25] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 26] = zValue;
			vertices[index + 27] = normal[0];
			vertices[index + 28] = normal[1];
			vertices[index + 29] = normal[2];

			vertices[index + 30] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 31] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 32] = 0.0f;
			vertices[index + 33] = normal[0];
			vertices[index + 34] = normal[1];
			vertices[index + 35] = normal[2];

			//second triangle

			vertices[index + 36] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 37] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 38] = 0.0f;

			vertices[index + 42] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 43] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 44] = 0.0f;

			vertices[index + 48] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 49] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 50] = zValue;

			U[0] = vertices[index + 42] - vertices[index + 36];
			U[1] = vertices[index + 43] - vertices[index + 37];
			U[2] = vertices[index + 44] - vertices[index + 38];

			V[0] = vertices[index + 48] - vertices[index + 36];
			V[1] = vertices[index + 49] - vertices[index + 37];
			V[2] = vertices[index + 50] - vertices[index + 38];

			normal[0] = U[1] * V[2] - U[2] * V[1];
			normal[1] = U[2] * V[0] - U[0] * U[2];
			normal[2] = U[0] * V[1] - U[1] * V[0];

			vertices[index + 39] = vertices[index + 45] = vertices[index + 51] = normal[0];
			vertices[index + 40] = vertices[index + 46] = vertices[index + 52] = normal[1];
			vertices[index + 41] = vertices[index + 47] = vertices[index + 53] = normal[2];

			vertices[index + 54] = radius * cos((i + 1) * circleQuantum);
			vertices[index + 55] = radius * sin((i + 1) * circleQuantum);
			vertices[index + 56] = zValue;
			vertices[index + 57] = normal[0];
			vertices[index + 58] = normal[1];
			vertices[index + 59] = normal[2];

			vertices[index + 60] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 61] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 62] = zValue;
			vertices[index + 63] = normal[0];
			vertices[index + 64] = normal[1];
			vertices[index + 65] = normal[2];

			vertices[index + 66] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
			vertices[index + 67] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
			vertices[index + 68] = 0.0f;
			vertices[index + 69] = normal[0];
			vertices[index + 70] = normal[1];
			vertices[index + 71] = normal[2];

			index += 72;
		}
	}

	const size_t verticeCoordNo = 6;
	const GLfloat radius = 1.0f;

	const size_t segmentsNo;
	const size_t verticesNo = 24 * segmentsNo;
	const GLfloat circleQuantum = 2 * M_PI/segmentsNo;

	GLuint VBO;
	GLuint VAO;

	GLfloat *vertices;
};

#endif
