#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <GL/glew.h>
#include <string.h>

class Platform
{
public:
	Platform(GLfloat sideWidth) {
		GLfloat height = 0.01f;
		GLfloat tempVertices[] = {
	        -0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 0.0f,
	         0.5f * sideWidth, -height, -0.5f * sideWidth,  1.0f, 0.0f,
	         0.5f * sideWidth,  height, -0.5f * sideWidth,  1.0f, 1.0f,
	         0.5f * sideWidth,  height, -0.5f * sideWidth,  1.0f, 1.0f,
	        -0.5f * sideWidth,  height, -0.5f * sideWidth,  0.0f, 1.0f,
	        -0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 0.0f,

	        -0.5f * sideWidth, -height,  0.5f * sideWidth,  0.0f, 0.0f,
	         0.5f * sideWidth, -height,  0.5f * sideWidth,  1.0f, 0.0f,
	         0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 1.0f,
	         0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 1.0f,
	        -0.5f * sideWidth,  height,  0.5f * sideWidth,  0.0f, 1.0f,
	        -0.5f * sideWidth, -height,  0.5f * sideWidth,  0.0f, 0.0f,

	        -0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 0.0f,
	        -0.5f * sideWidth,  height, -0.5f * sideWidth,  1.0f, 1.0f,
	        -0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 1.0f,
	        -0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 1.0f,
	        -0.5f * sideWidth, -height,  0.5f * sideWidth,  0.0f, 0.0f,
	        -0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 0.0f,

	         0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 0.0f,
	         0.5f * sideWidth,  height, -0.5f * sideWidth,  1.0f, 1.0f,
	         0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 1.0f,
	         0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 1.0f,
	         0.5f * sideWidth, -height,  0.5f * sideWidth,  0.0f, 0.0f,
	         0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 0.0f,

	        -0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 1.0f,
	         0.5f * sideWidth, -height, -0.5f * sideWidth,  1.0f, 1.0f,
	         0.5f * sideWidth, -height,  0.5f * sideWidth,  1.0f, 0.0f,
	         0.5f * sideWidth, -height,  0.5f * sideWidth,  1.0f, 0.0f,
	        -0.5f * sideWidth, -height,  0.5f * sideWidth,  0.0f, 0.0f,
	        -0.5f * sideWidth, -height, -0.5f * sideWidth,  0.0f, 1.0f,

	        -0.5f * sideWidth,  height, -0.5f * sideWidth,  0.0f, 1.0f,
	         0.5f * sideWidth,  height, -0.5f * sideWidth,  1.0f, 1.0f,
	         0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 0.0f,
	         0.5f * sideWidth,  height,  0.5f * sideWidth,  1.0f, 0.0f,
	        -0.5f * sideWidth,  height,  0.5f * sideWidth,  0.0f, 0.0f,
	        -0.5f * sideWidth,  height, -0.5f * sideWidth,  0.0f, 1.0f
	    };

		vertices = new GLfloat[trianglesNo*verticeCoordNo];

		memcpy(vertices, tempVertices, sizeof(GLfloat)*trianglesNo*verticeCoordNo);
	}

	~Platform() {
		delete[] vertices;
	}

	GLfloat *GetVertices() {
		return vertices;
	}

	size_t GetArraySize() {
		return sizeof(GLfloat)*trianglesNo*verticeCoordNo;
	}

	size_t GetTrianglesNo() {
		return trianglesNo;
	}

private:
	const size_t trianglesNo = 6*6;
	const size_t verticeCoordNo = 5;
	GLfloat *vertices;
};

#endif
