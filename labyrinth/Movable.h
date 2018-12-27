#pragma once
#include <glm/vec3.hpp>
#include <Gl/freeglut.h>

class Movable
{
public:
	GLfloat speedFactor = 1.0;

	glm::tvec3 <GLfloat> position;
	glm::tvec3 <GLfloat> targetPosition;

	void move(const GLfloat dt) {
		position = position + (targetPosition - position)*dt*speedFactor;
	}

	Movable() {
		position.x = position.y = position.z = 0;
		targetPosition.x = targetPosition.y = targetPosition.z = 0;
	}
};

