#pragma once
#include <vector>
#include <list>
#include "mazeGenerator.h"
#include "Cube.h"
#include "Camera.h"
#include "Player.h"
#include "Lamp.h"
#include "Ground.h"

class Scene
{
	Camera camera;
	std::vector <Cube> cubeContainer;
	Lamp lamp1;
	Lamp lamp2;
	Ground ground;

public:
	const int width;
	const int height;
	Node *labyrinth = nullptr;

	Player player;

	void update(GLfloat);

	Camera &getCamera();
	std::vector <Drawable*> getDrawables(void);

	char& getThingIn(const int n, const int k) const;
	
	Scene(const int, const int);
	~Scene();
};

