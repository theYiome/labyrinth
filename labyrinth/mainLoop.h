#pragma once
//https://www.reddit.com/r/gamedev/comments/41v2td/a_modern_c_game_loop_template_mit/
#include <chrono>
#include "drawWorld.h"
#include "Scene.h"

using namespace std::chrono_literals;

static Scene mainScene;

void mainLoop() {
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	static auto time_start = clock::now();

	auto dt = clock::now() - time_start;
	time_start = clock::now();

	/*
	update game logic
	and render updated stuff below
	*/
	
	drawWorld(mainScene.getDrawables());
	
}

