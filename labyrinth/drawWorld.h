#pragma once
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <vector>
#include "materials.h"
#include "Drawable.h"
#include "Camera.h"
#include <iostream>

static GLfloat dt = 0;
static const GLfloat width = 15, height = 21, depth = 0.24;


void drawWorld(const std::vector<Drawable*> toDraw, Camera &cam) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		cam.position.x, cam.position.y, cam.position.z, 
		cam.lookAt.x, cam.lookAt.y, cam.lookAt.z,
		cam.rotation.x, cam.rotation.y, cam.rotation.z
	);

	for (Drawable* var : toDraw) var->draw();

	glutSwapBuffers();
	glutPostRedisplay();
}
