#pragma once
#include <vector>
#include "Cube.h"
#include "Camera.h"
#include "Player.h"
#include "mazeGenerator.h"

class Scene
{
	Camera camera;
	std::vector <Cube> cubeContainer;

public:
	const int width = 5;
	const int height = 9;
	Node *labyrinth = nullptr;

	Player player;

	void update(GLfloat);

	Camera &getCamera();
	std::vector <Drawable*> getDrawables(void);

	const char getThingIn(const int n, const int k) const;
	
	Scene();
	~Scene();
};

