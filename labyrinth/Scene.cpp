#include "Scene.h"
#include "mazeGenerator.h"
#include <random>

Skybox* Scene::skybox = nullptr;

static const GLfloat multi = 0.8f;

void Scene::update(GLfloat dt) {
	//move player
	player.targetPosition.x = 0.5f * player.squarePosition.x;
	player.targetPosition.y = 0.5f * player.squarePosition.y;
	player.move(dt);

	//move camera
	camera.targetPosition.x = player.position.x + 5.0;
	camera.targetPosition.y = player.position.y - 1;
	camera.move(dt);

	//move skybox so it is static for camera
	skybox->position = camera.position;

	lamp1.targetPosition.x = player.position.x + 0;
	lamp1.targetPosition.y = player.position.y + 0;
	lamp1.targetPosition.z = player.position.z + 1.0;

	lamp1.move(dt);
	lamp2.move(dt);

	//adjust "look at" place to fit player position
	camera.lookAt = camera.lookAt + (player.position - camera.lookAt)*dt*multi;
}

Camera& Scene::getCamera() {
	return camera;
}

std::vector<Drawable*> Scene::getDrawables(void) {
	std::vector<Drawable*> toDraw;

	toDraw.push_back(&player);
	toDraw.push_back(&lamp1);
	toDraw.push_back(&lamp2);
	toDraw.push_back(&ground);
	toDraw.push_back(skybox);
	for (auto &var : cubeContainer) toDraw.push_back(&var);

	return toDraw;
}

char& Scene::getThingIn(const int n, const int k) const {
	return labyrinth[k + n * width].c;
}

Scene::Scene(const int w, const int h) : width(w), height(h), ground(w, h) {

	//https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
	//seting generator up to generate random colors for lamps
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	//generating the labyrinth
	labyrinth = generateLabyrinth(width, height);


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (labyrinth[j + i * width].c == '#') cubeContainer.push_back(Cube(i, j));
		}
	}



	Cube finalCube(height - 2, width - 2);
	finalCube.color.g = 0.8;
	finalCube.color.b = 0;
	finalCube.color.r = 0;


	cubeContainer.push_back(finalCube);
	getThingIn(height - 2, width - 2) = '!';

	//companion torus color
	lamp1.DIFFUSE[0] = dist(mt);
	lamp1.DIFFUSE[1] = dist(mt);
	lamp1.DIFFUSE[2] = dist(mt);

	//end torus placement and color
	glm::tvec3 <GLfloat> temp;
	temp.x = height * 0.5 - 1;
	temp.y = width * 0.5 - 1;
	temp.z = 2;

	lamp2.targetPosition = temp;
	lamp2.DIFFUSE[0] = dist(mt);
	lamp2.DIFFUSE[1] = dist(mt);
	lamp2.DIFFUSE[2] = dist(mt);

	lamp2.position.x = -32;
	lamp2.position.y = -32;
	lamp2.position.z = 6;

}


Scene::~Scene() {
	//delete labyrinth;
}
