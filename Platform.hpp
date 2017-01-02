#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

#include <GL/glew.h>
#include <string.h>
#include <SOIL/SOIL.h>

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

	    glGenTextures(1, &texture);
	    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	    // Set our texture parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    // Set texture filtering
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    // Load, create texture and generate mipmaps
	    int width, height;
	    unsigned char* image = SOIL_load_image("ground.png", &width, &height, 0, SOIL_LOAD_RGB);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	    glGenerateMipmap(GL_TEXTURE_2D);
	    SOIL_free_image_data(image);
	    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
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

	GLuint GetTexture() {
		return texture;
	}

private:
	const size_t verticesNo = 6*6;
	const size_t verticeCoordNo = 5;
	const GLfloat height = 0.01f;

	GLuint VBO;
	GLuint VAO;
	GLuint texture;

	GLfloat *vertices;
};

#endif
