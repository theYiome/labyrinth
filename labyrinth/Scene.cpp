#include "Scene.h"
#include "mazeGenerator.h"


static const GLfloat multi = 2.f;

void Scene::update(GLfloat dt)
{
	player.update(dt);

	camera.target = camera.target + (player.position - camera.target)*dt*multi;

	static glm::tvec3 <GLfloat> tempPlayerPos;

	tempPlayerPos.x = 0.5f * player.squarePosition.x;
	tempPlayerPos.y = 0.5f * player.squarePosition.y;
	tempPlayerPos.z = player.position.z;

	player.position = player.position + (tempPlayerPos - player.position)*dt*12.f;

	static glm::tvec3 <GLfloat> tempCam;
	tempCam = camera.position;
	tempCam.z = 0.f;

	static glm::tvec3 <GLfloat> tempPlay;
	tempPlay = player.position;
	tempPlay.z = 0.f;
	tempPlay.x += 5.f;

	camera.position = camera.position + (tempPlay - tempCam)*dt;

	camera.position.z = camera.desiredHeight;

	camera.update(dt);
	for (auto &var : cubeContainer) var.update(dt);
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
