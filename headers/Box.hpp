#ifndef BOX_HPP_
#define BOX_HPP_

#include "Object.hpp"

#include <string>

class Box : public Object
{
public:
	Box(GLfloat width, GLfloat height, GLfloat depth);
	~Box();

	void SetTexture(std::string texPath);
	void Draw(glm::vec3 &lightPos, glm::mat4 &model, glm::vec3 lightColor);

private:
	void BindVertices();

	const GLfloat height = 1.01f;
};

#endif
