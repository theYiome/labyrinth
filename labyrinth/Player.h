#pragma once
#include "Drawable.h"
#include "GLM/vec3.hpp"
#include "GLM/vec2.hpp"
#include "GL/freeglut.h"

class Player :
	public Drawable
{

public:

	glm::ivec2 squarePosition;

	glm::tvec3 <GLfloat> position;
	glm::tvec3 <GLfloat> velocity;

	Player();
	
	void draw(void);

	void update(GLfloat);
};

