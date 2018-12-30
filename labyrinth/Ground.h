#pragma once
#include "Drawable.h"
#include "GL/freeglut.h"

class Ground : public Drawable 
{
public:
	GLfloat xOffset, yOffset, zOffset;
	GLfloat tileSize;
	GLint width, height;

	void draw(void);

	Ground(int, int);
};

