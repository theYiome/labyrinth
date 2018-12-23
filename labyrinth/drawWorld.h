#pragma once
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <vector>
#include "materials.h"
#include "Drawable.h"
#include "Camera.h"


void drawWorld(const std::vector<Drawable*> toDraw, Camera &cam) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		cam.position.x, cam.position.y, cam.position.z, 
		cam.target.x, cam.target.y, cam.target.z,
		cam.rotation.x, cam.rotation.y, cam.rotation.z
	);

	GLfloat light_position[4] = { 2, -2, 3, 0};           //new
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);       //new
	glEnable(GL_COLOR);

	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0, 1.0, 1.0);
	//	glVertex3f(7, 0, -0.5);
	//	glVertex3f(-7, -7, -0.5);
	//	glVertex3f(-7, 7, -0.5);
	//glEnd();

	//glDisable(GL_COLOR_MATERIAL);
	//glDisable(GL_COLOR);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, testAmbient);        //new
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, testDiffuse);        //new
	//glMaterialfv(GL_FRONT, GL_SPECULAR, testSpecular);      //new
	//glMaterialf(GL_FRONT, GL_SHININESS, testShininess);     //new

	for (Drawable* var : toDraw) var->draw();
	

	glutSwapBuffers();
	glutPostRedisplay();
}
