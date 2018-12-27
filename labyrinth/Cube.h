#pragma once
#include "Drawable.h"
#include "GLM/vec3.hpp"
#include <GL/freeglut.h>
#include "Movable.h"

class Cube : public Drawable, public Movable
{
public:

	GLfloat size = 0.5;

	glm::tvec3 <GLfloat> color;

	void draw(void);

	Cube(int, int);
};

