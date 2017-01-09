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
	:Object(36, 8) {
		GLfloat tempVertices[] = {
	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
	        -0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

	        -0.5f * width, -0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,		0.0f, 0.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,		1.0f, 0.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
	        -0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,		0.0f, 1.0f,
	        -0.5f * width, -0.5f * height,  0.5f * depth,	0.0f,  0.0f,  1.0f,		0.0f, 0.0f,

	        -0.5f * width,  0.5f * height,  0.5f * depth,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	        -0.5f * width,  0.5f * height, -0.5f * depth,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	        -0.5f * width, -0.5f * height,  0.5f * depth,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
	        -0.5f * width,  0.5f * height,  0.5f * depth,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

	         0.5f * width,  0.5f * height,  0.5f * depth,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
	         0.5f * width, -0.5f * height, -0.5f * depth,	0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
	         0.5f * width, -0.5f * height,  0.5f * depth,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
	        -0.5f * width, -0.5f * height,  0.5f * depth,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
	        -0.5f * width, -0.5f * height, -0.5f * depth,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

	        -0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
	         0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
	         0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
	        -0.5f * width,  0.5f * height,  0.5f * depth,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
	        -0.5f * width,  0.5f * height, -0.5f * depth,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f
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

	void SetTexture(std::string texPath) {
		glGenTextures(1, &texture);
	    int width, height;
	    unsigned char* image;
	    // Diffuse map
	    image = SOIL_load_image(texPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	    glBindTexture(GL_TEXTURE_2D, texture);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	    glGenerateMipmap(GL_TEXTURE_2D);
	    SOIL_free_image_data(image);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	    glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Draw(glm::vec3 &lightPos, glm::mat4 &model) {
		shader->Use();
		glUniform1i(glGetUniformLocation(shader->Program, "material.diffuse"), 0);
		glUniform3f(glGetUniformLocation(shader->Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader->Program, "viewPos"), camera->Position.x, camera->Position.y, camera->Position.z);
		// Set lights properties
		glUniform3f(glGetUniformLocation(shader->Program, "light.ambient"),  0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(shader->Program, "light.diffuse"),  0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(shader->Program, "light.specular"), 0.5f, 0.5f, 0.5f);
		// Set material properties
		glUniform3f(glGetUniformLocation(shader->Program, "material.specular"),  0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(shader->Program, "material.shininess"), 64.0f);


		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera->Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		glBindTexture(GL_TEXTURE_2D, GetTexture());

		// Draw the container (using container's vertex attributes)
		glBindVertexArray(GetVAO());
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, GetVerticesNo());
		glBindVertexArray(0);
	}

private:
	void BindVertices() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		    // Bind our Vertex Array Object first, then bind and set our buffers and pointers.
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, GetArraySize(), GetVertices(), GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);

		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	const GLfloat height = 1.01f;
};

#endif
