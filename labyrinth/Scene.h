#pragma once
#include <vector>
#include <list>
#include "mazeGenerator.h"
#include "Cube.h"
#include "Camera.h"
#include "Player.h"
#include "Lamp.h"

class Scene
{
	Camera camera;
	std::vector <Cube> cubeContainer;
	Lamp lamp1;
	Lamp lamp2;

public:
	const int width = 29;
	const int height = 29;
	Node *labyrinth = nullptr;

	Player player;

	void update(GLfloat);

	Camera &getCamera();
	std::vector <Drawable*> getDrawables(void);

	const char getThingIn(const int n, const int k) const;
	
	Scene();
	~Scene();
};

