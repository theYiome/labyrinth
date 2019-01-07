#pragma once
//https://www.reddit.com/r/gamedev/comments/41v2td/a_modern_c_game_loop_template_mit/
//https://stackoverflow.com/questions/14391327/how-to-get-duration-as-int-millis-and-float-seconds-from-chrono
#include <chrono>
#include "drawWorld.h"
#include "Scene.h"
#include "vecLenght.h"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;

using namespace std::chrono_literals;

static Scene* currentScene = nullptr;

void shutdown() {
	delete currentScene;
}

bool nextScene = false;

static const GLfloat ANIMATION_TIME = 2;

static bool checkSceneStatus(GLfloat dt) {
	static GLfloat timeLeft = ANIMATION_TIME;

	if (currentScene == nullptr) {
		//Startup, first labyrinth, first scene
		currentScene = new Scene(11, 3);
		Scene::skybox = new Skybox("RESOURCES/dark.png");
	}
	else if (nextScene == true) {
		const GLfloat POS = 36;
		currentScene->getCamera().targetPosition.x = POS;
		currentScene->getCamera().targetPosition.y = POS;
		currentScene->getCamera().targetPosition.z = POS;

		currentScene->lamp1.move(dt);
		currentScene->lamp2.move(dt);

		currentScene->player.move(dt);

		currentScene->getCamera().move(dt);
		Scene::skybox->position = currentScene->getCamera().targetPosition;


		timeLeft -= dt;
		if (timeLeft < 0) {
			const int newWidth = currentScene->height + 2;
			const int newHeight = currentScene->width + 2;

			delete currentScene;
			currentScene = new Scene(newWidth, newHeight);
			nextScene = false;
			timeLeft = ANIMATION_TIME;
		}
		return false;
	}

	return true;
}

static GLfloat secondsTimer = 0;
static int fpsCount = 0;

void mainLoop() {

	//getting delta time
	static auto t0 = Time::now();
	ms fs = std::chrono::duration_cast<ms>(Time::now() - t0);
	GLfloat dt = fs.count()/(1000.0);

	//fps measurement
	secondsTimer += dt;
	fpsCount++;

	if (secondsTimer > 1) {
		std::cout << "FPS: "<< fpsCount <<std::endl;
		fpsCount = 0;
		secondsTimer = 0;
	}

	//fixing if dt gets to high
	dt = dt < 0.03 ? dt : 0.03;
	t0 = Time::now();


	/*
	update game logic
	and render updated stuff below
	*/

	if(checkSceneStatus(dt)) currentScene->update(dt);

	
	drawWorld(currentScene->getDrawables(), currentScene->getCamera());
	
}

