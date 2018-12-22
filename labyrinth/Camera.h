#pragma once
#include <glm/vec3.hpp>
#include <GL/freeglut.h>
class Camera
{
public:
	glm::tvec3 <GLfloat> position;
	glm::tvec3 <GLfloat> target;
	glm::tvec3 <GLfloat> rotation;

	glm::tvec3 <GLfloat> velocity;
};

