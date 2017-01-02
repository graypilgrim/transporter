#ifndef GEAR_HPP
#define GEAR_HPP

#include <GL/glew.h>
#include <string.h>

class Gear
{
public:
	Gear(size_t segments)
	:segmentsNo(segments) {
		vertices = new GLfloat[verticesNo * verticeCoordNo];

		memset(vertices, 0, this->GetArraySize());

		DrawCircles();
	}

	~Gear() {
	}

	GLfloat *GetVertices() {
		return vertices;
	}

	size_t GetVerticesNo() {
		return verticesNo;
	}

	size_t GetArraySize() {
		return sizeof(GLfloat) * verticesNo * verticeCoordNo;
	}

private:
	void DrawCircles() {

	}

	const size_t verticesNo = 24 * segmentsNo;
	const size_t verticeCoordNo = 3;

	const size_t segmentsNo;

	GLfloat *vertices;
};

#endif
