#pragma once
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <vector>
#include "materials.h"
#include "Drawable.h"


void drawWorld(const std::vector<Drawable*> &toDraw)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(3, 3, 3, 0, 0, 0, 0, 0, 1);

	//GLfloat light0_position[4] = { 0, -10, -10, 0.5 };

	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	for (Drawable* var : toDraw) var->draw();
	

	glutSwapBuffers();
	glutPostRedisplay();
}