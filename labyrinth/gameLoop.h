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

static void checkSceneStatus(GLfloat dt) {
	static GLfloat timeLeft = 3.0;

	if (currentScene == nullptr) currentScene = new Scene(3, 9);
	else if (nextScene == true) {
		currentScene->getCamera().targetPosition.z = 64;
		timeLeft -= dt;
		if (timeLeft < 0) {
			const int newWidth = currentScene->height + 2;
			const int newHeight = currentScene->width + 2;

			delete currentScene;
			currentScene = new Scene(newWidth, newHeight);
			nextScene = false;
			timeLeft = 3.0;
		}
	}
}


void mainLoop() {

	//getting delta time
	static auto t0 = Time::now();
	ms fs = std::chrono::duration_cast<ms>(Time::now() - t0);
	GLfloat dt = fs.count()/(1000.0);

	//fixing if dt gets to high
	dt = dt < 0.03 ? dt : 0.03;
	t0 = Time::now();

	checkSceneStatus(dt);

	/*
	update game logic
	and render updated stuff below
	*/

	currentScene->update(dt);
	
	drawWorld(currentScene->getDrawables(), currentScene->getCamera());
	
}

