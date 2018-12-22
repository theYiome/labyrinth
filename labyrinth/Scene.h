#pragma once
#include <vector>
#include "Cube.h"

class Scene
{
	std::vector <Cube> cubeContainer;
public:

	void update(GLfloat);

	std::vector <Drawable*> getDrawables(void);

	Scene();
	~Scene();
};

