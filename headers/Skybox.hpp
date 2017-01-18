#ifndef SKYBOX_HPP_
#define SKYBOX_HPP_

#include <vector>
#include <string>

#include "Object.hpp"

class Skybox : public Object
{
public:
	Skybox();
	~Skybox();

	void Draw();

private:
	void LoadCubemap();
	void BindVertices();

	std::vector<std::string> faces;
};

#endif
