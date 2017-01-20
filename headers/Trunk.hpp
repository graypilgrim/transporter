#ifndef TRUNK_HPP_
#define TRUNK_HPP_

#include "Object.hpp"

class Trunk : public Object
{
public:
	Trunk(size_t segments);
	~Trunk();

	void Draw(glm::vec3 &lightPos, glm::mat4 &model, glm::vec3 lightColor);

private:
	void BindVertices();
	void BindTexture();
	void CreateCircles(size_t &index, GLfloat height);
	void CreateCircle(size_t &index, GLfloat zValue);
	void CreateSides(size_t &index, GLfloat zValue);

	const GLfloat radius = 0.1f;

	const size_t segmentsNo;
	const GLfloat circleQuantum = 2 * M_PI/segmentsNo;

};

#endif
