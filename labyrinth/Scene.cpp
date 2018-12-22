#include "Scene.h"

void Scene::update(void)
{
}

std::vector<Drawable*> Scene::getDrawables(void)
{
	std::vector<Drawable*> toDraw;
	for (auto var : cubeContainer) {
		toDraw.push_back(&var);
	}

	return toDraw;
}

Scene::Scene()
{
	cubeContainer.push_back(Cube());
}


Scene::~Scene()
{
}
