#ifndef BOX_HPP_
#define BOX_HPP_

#include "Object.hpp"

#include <GL/glew.h>
#include <string.h>
#include <SOIL/SOIL.h>

class Box : public Object
{
public:
	Box(GLfloat width, GLfloat height, GLfloat depth)
	:Object(36, 6) {
		GLfloat tempVertices[] = {
	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,
	        -0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,

	        -0.5f * width, -0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,
	        -0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,
	        -0.5f * width, -0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,

	        -0.5f * width,  0.5f * height,  0.5f * depth,	-1.0f,  0.0f,  0.0f,
	        -0.5f * width,  0.5f * height, -0.5f * depth,	-1.0f,  0.0f,  0.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	-1.0f,  0.0f,  0.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	-1.0f,  0.0f,  0.0f,
	        -0.5f * width, -0.5f * height,  0.5f * depth,	-1.0f,  0.0f,  0.0f,
	        -0.5f * width,  0.5f * height,  0.5f * depth,	-1.0f,  0.0f,  0.0f,

	         0.5f * width,  0.5f * height,  0.5f * depth,	1.0f,  0.0f,  0.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	1.0f,  0.0f,  0.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	1.0f,  0.0f,  0.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	1.0f,  0.0f,  0.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	1.0f,  0.0f,  0.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	1.0f,  0.0f,  0.0f,

	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f, -1.0f,  0.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	0.0f, -1.0f,  0.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	0.0f, -1.0f,  0.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	0.0f, -1.0f,  0.0f,
	        -0.5f * width, -0.5f * height,  0.5f * depth,	0.0f, -1.0f,  0.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f, -1.0f,  0.0f,

	        -0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  1.0f,  0.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  1.0f,  0.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  1.0f,  0.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  1.0f,  0.0f,
	        -0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  1.0f,  0.0f,
	        -0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  1.0f,  0.0f,
	    };

		vertices = new GLfloat[verticesNo * verticeCoordNo];

		memcpy(vertices, tempVertices, GetArraySize());

		BindVertices();
	}

	~Box() {
		delete[] vertices;
		glDeleteVertexArrays(1, &VAO);
	    glDeleteBuffers(1, &VBO);
	}

	void BindTexture() {
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
	const GLfloat height = 1.01f;
};

#endif
