#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <GL/freeglut.h>
#include "Drawable.h"
#include <string>

class Skybox : public Drawable {

public:

	glm::tvec3 <GLfloat> position;

	GLfloat size = 80;

	int width, height, nrChannels;

	unsigned char *data;
	unsigned int TEXTURE_ID;

	Skybox(std::string filename);

	void draw(void);

};