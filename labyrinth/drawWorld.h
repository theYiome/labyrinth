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

	dt += 0.001;
	//std::cout << dt << std::endl;


	glPushMatrix();
		glColor3f(0.2, 0.2, 0.2);
		glTranslatef(0, 0, 0.24);
		glRectf(-0.25, -0.25, height*0.5f - 0.25, width*0.5f - 0.25);
	glPopMatrix();

	for (Drawable* var : toDraw) var->draw();
	

	glutSwapBuffers();
	glutPostRedisplay();
}
