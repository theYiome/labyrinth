#pragma once
#include <glm/vec3.hpp>
#include <GL/freeglut.h>
#include "Movable.h"

class Camera : public Movable
{
public:
	glm::tvec3 <GLfloat> lookAt;
	glm::tvec3 <GLfloat> rotation;

	Camera() {
		const GLfloat k = 32;
		position.x = position.y = position.z = k;
		targetPosition.x = targetPosition.y = targetPosition.z = 6.f;

		lookAt.x = lookAt.y = lookAt.z = 0;

		rotation.x = rotation.y = 0;
		rotation.z = 1.f;
	}
};

