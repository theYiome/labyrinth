#pragma once
#include <glm/vec3.hpp>
#include <GL/freeglut.h>
class Camera
{
public:
	GLfloat desiredHeight = 6.f;

	glm::tvec3 <GLfloat> position;
	glm::tvec3 <GLfloat> target;
	glm::tvec3 <GLfloat> rotation;

	glm::tvec3 <GLfloat> velocity;

	Camera() {
		position.x = position.y = position.z = 6.f;
		target.x = target.y = target.z = 0;
		rotation.x = rotation.y = 0;
		rotation.z = 1.f;

	}

	void update(GLfloat dt) {
		position = position + (velocity*dt);
	}
};

