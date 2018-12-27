#pragma once
#include "Drawable.h"
#include "GLM/vec3.hpp"
#include "GLM/vec2.hpp"
#include "GL/freeglut.h"
#include "Movable.h"

class Player : public Drawable, public Movable
{

public:

	glm::ivec2 squarePosition;

	glm::tvec3 <GLfloat> velocity;

	Player();
	
	void draw(void);
};

