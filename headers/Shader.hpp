#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();

	GLuint Program;
};

#endif
