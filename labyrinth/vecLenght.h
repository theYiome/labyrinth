#pragma once
#include <glm/vec3.hpp>
#include <GL/freeglut.h>
#include <math.h>

template <class T>

GLfloat tvecLength3v(const glm::tvec3 <T> vec) {
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}