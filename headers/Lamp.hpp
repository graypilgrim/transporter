#ifndef LAMP_HPP_
#define LAMP_HPP_

#include "Box.hpp"

class Lamp : public Box
{
public:
	Lamp(GLfloat width, GLfloat height, GLfloat depth);
	void Draw(glm::vec3 &lightPos, glm::mat4 &model);
};
#endif
