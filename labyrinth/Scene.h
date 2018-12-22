#pragma once
#include <vector>
#include "Cube.h"

class Scene
{
	std::vector <Cube> cubeContainer;
public:

	void update(void);

	std::vector <Drawable*> getDrawables(void);

	Scene();
	~Scene();
};
