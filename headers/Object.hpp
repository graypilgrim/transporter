#ifndef OBJECT_HPP_
#define OBJECT_HPP_

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
	Object(size_t vertices, size_t coordinatesNo);

	GLfloat *GetVertices();
	size_t GetVerticesNo();
	size_t GetArraySize();
	GLuint GetVAO();
	GLuint GetVBO();
	GLuint GetTexture();

	void SetCamera(Camera *c);
	void SetShader(Shader *s);

protected:
	void BindVertices();

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
