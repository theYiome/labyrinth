#pragma once
#include "Drawable.h"
#include "GLM/vec3.hpp"
#include <GL/freeglut.h>

class Cube :
	public Drawable
{
	glm::tvec3 <GLfloat> position;
	glm::tvec3 <GLfloat> velocity;
	GLfloat size = 0.5;

public:
	glm::tvec3 <GLfloat> color;
	Cube(int, int);
	~Cube() = default;
	void draw(void);
	void update(GLfloat);
};

