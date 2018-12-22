#pragma once
#include "Drawable.h"
#include "GLM/vec3.hpp"
#include <GL/freeglut.h>

class Cube :
	public Drawable
{
	glm::tvec3 <GLfloat> position;
	glm::tvec3 <GLfloat> velocity;
	glm::tvec3 <GLfloat> color;
	GLfloat size = 0.5;

public:
	Cube(GLfloat, GLfloat);
	~Cube() = default;
	void draw(void);
	void update(GLfloat);
};

