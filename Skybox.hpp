#ifndef SKYBOX_HPP_
#define SKYBOX_HPP_

#include <vector>

#include "Object.hpp"

class Skybox : public Object
{
public:
	Skybox()
	:Object(36, 3) {
		GLfloat skyboxVertices[] = {
			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f
		};

		vertices = new GLfloat[verticesNo * verticeCoordNo];

		memcpy(vertices, skyboxVertices, GetArraySize());

	    faces.push_back("skybox/right.jpg");
	    faces.push_back("skybox/left.jpg");
	    faces.push_back("skybox/top.jpg");
	    faces.push_back("skybox/bottom.jpg");
	    faces.push_back("skybox/back.jpg");
	    faces.push_back("skybox/front.jpg");

		BindVertices();
	    LoadCubemap();
	}

private:
	void LoadCubemap()
	{
		glActiveTexture(GL_TEXTURE0);
	    glGenTextures(1, &texture);


	    int width, height;
	    unsigned char* image;

	    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	    for (GLuint i = 0; i < faces.size(); i++)
	    {
	        image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	    }
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void BindVertices() {
		    glGenVertexArrays(1, &VAO);
		    glGenBuffers(1, &VBO);
		    glBindVertexArray(VAO);
		    glBindBuffer(GL_ARRAY_BUFFER, VBO);
		    glBufferData(GL_ARRAY_BUFFER, GetArraySize(), GetVertices(), GL_STATIC_DRAW);
		    glEnableVertexAttribArray(0);
		    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
		    glBindVertexArray(0);
	}

	std::vector<std::string> faces;
};

#endif
