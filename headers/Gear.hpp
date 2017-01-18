#ifndef GEAR_HPP
#define GEAR_HPP

#include "Object.hpp"

class Gear : public Object
{
public:
	Gear(size_t segments);
	~Gear();

	void Draw(glm::vec3 &lightPos, glm::mat4 &model);

private:
	void CreateCircles(size_t &index, GLfloat height);
	void CreateCircle(size_t &index, GLfloat zValue);
	void CreateSides(size_t &index, GLfloat zValue);

	const GLfloat radius = 0.2f;

	const size_t segmentsNo;
	const GLfloat circleQuantum = 2 * M_PI/segmentsNo;
};

#endif
