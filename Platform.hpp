#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

#include <GL/glew.h>
#include <string.h>

class Platform
{
public:
	Platform(GLfloat sideWidth) {
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

		vertices = new GLfloat[verticesNo * verticeCoordNo];

		memcpy(vertices, tempVertices, sizeof(GLfloat) * verticesNo * verticeCoordNo);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		    // Bind our Vertex Array Object first, then bind and set our buffers and pointers.
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->GetArraySize(), this->GetVertices(), GL_STATIC_DRAW);

		    // Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);
		    // TexCoord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	~Platform() {
		delete[] vertices;
		glDeleteVertexArrays(1, &VAO);
	    glDeleteBuffers(1, &VBO);
	}

	GLfloat *GetVertices() {
		return vertices;
	}

	size_t GetArraySize() {
		return sizeof(GLfloat) * verticesNo * verticeCoordNo;
	}

	size_t GetVerticesNo() {
		return verticesNo;
	}

	GLuint GetVAO() {
		return VAO;
	}

	GLuint GetVBO() {
		return VBO;
	}

private:
	const size_t verticesNo = 6*6;
	const size_t verticeCoordNo = 5;
	const GLfloat height = 0.01f;

	GLuint VBO;
	GLuint VAO;

	GLfloat *vertices;
};

#endif
