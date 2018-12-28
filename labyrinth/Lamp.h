#pragma once
#include <array>
#include <GL/freeglut.h>
#include "Drawable.h"
#include "Movable.h"

#define NO_RESOURCE -1

class Lamp : public Drawable, public Movable
{
	static const int MAX_LIGHTS = 7;
	static const std::array<int, MAX_LIGHTS> LIGHTS_ENUM;
	static int lightAvailable[MAX_LIGHTS];

	static const int getFirstAvailableID();
public:

	int ID = NO_RESOURCE;

	GLfloat AMBIENT[4] = {0};
	GLfloat DIFFUSE[4] = {0, 0, 0, 0};
	GLfloat SPECULAR[4] = {1, 1, 1, 0};

	void draw(void);

	void move(GLfloat dt);

	Lamp();

	Lamp(Lamp&);

	~Lamp();
};