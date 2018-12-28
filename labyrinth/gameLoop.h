#pragma once
//https://www.reddit.com/r/gamedev/comments/41v2td/a_modern_c_game_loop_template_mit/
//https://stackoverflow.com/questions/14391327/how-to-get-duration-as-int-millis-and-float-seconds-from-chrono
#include <chrono>
#include "drawWorld.h"
#include "Scene.h"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;

using namespace std::chrono_literals;

static Scene* currentScene = nullptr;

void shutdown() {
	delete currentScene;
}


void mainLoop() {
	if (currentScene == nullptr) currentScene = new Scene();

	//getting delta time
	static auto t0 = Time::now();
	ms fs = std::chrono::duration_cast<ms>(Time::now() - t0);
	GLfloat dt = fs.count()/(1000.0);

	//fixing if dt gets to high
	dt = dt < 0.03 ? dt : 0.03;
	t0 = Time::now();

	/*
	update game logic
	and render updated stuff below
	*/

	currentScene->update(dt);
	
	drawWorld(currentScene->getDrawables(), currentScene->getCamera());
	
}

