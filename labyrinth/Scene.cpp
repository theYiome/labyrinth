#include "Scene.h"
#include "mazeGenerator.h"


static const GLfloat multi = 2.f;

void Scene::update(GLfloat dt)
{
	//move player
	player.targetPosition.x = 0.5f * player.squarePosition.x;
	player.targetPosition.y = 0.5f * player.squarePosition.y;
	player.move(dt);

	//move camera
	camera.targetPosition.x = player.position.x + 5.0;
	camera.targetPosition.y = player.position.y + 0.5;
	camera.move(dt);

	//adjust "look at" place to fit player position
	camera.lookAt = camera.lookAt + (player.position - camera.lookAt)*dt*multi;
}

Camera& Scene::getCamera() {
	return camera;
}

std::vector<Drawable*> Scene::getDrawables(void) {
	std::vector<Drawable*> toDraw;

	toDraw.push_back(&player);
	for (auto &var : cubeContainer) toDraw.push_back(&var);

	return toDraw;
}

const char Scene::getThingIn(const int n, const int k) const
{
	return labyrinth[k + n * width].c;
}

Scene::Scene() {

	labyrinth = generateLabyrinth(width, height);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			if (labyrinth[j + i * width].c == '#') cubeContainer.push_back(Cube(i, j));
		}
	}

	Cube finalCube(height - 2, width - 2);
	finalCube.color.g = 0.8;
	finalCube.color.b = 0;
	finalCube.color.r = 0;


	cubeContainer.push_back(finalCube);
	labyrinth[width - 2 + height * (height - 2)].c == '!';
}


Scene::~Scene()
{
}
