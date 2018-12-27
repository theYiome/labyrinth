#pragma once
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <vector>
#include "materials.h"
#include "Drawable.h"
#include "Camera.h"
#include <iostream>


static GLfloat TEST_AMBIENT[4] = { 0, 0, 0, 1 };
static GLfloat TEST_DIFFUSE[4] = { 0.8, 0.8, 0.8, 1 };
static GLfloat TEST_SPECULAR[4] = {0.5, 0.5, 0.5, 1 };
static GLfloat TEST_SPECULAR2[4] = {0.5, 0, 0, 1 };

static GLfloat TEST_POSITION[4] = { 2, 3, 1, 1 };

static GLfloat dt = 0;


void drawWorld(const std::vector<Drawable*> toDraw, Camera &cam) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		cam.position.x, cam.position.y, cam.position.z, 
		cam.lookAt.x, cam.lookAt.y, cam.lookAt.z,
		cam.rotation.x, cam.rotation.y, cam.rotation.z
	);

	dt += 0.01;
	TEST_SPECULAR[0] = 0;
	//TEST_POSITION[0] = dt + 2;
	std::cout << dt << std::endl;


	//glEnable(GL_LIGHT0);
	//glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1);

	glEnable(GL_NORMALIZE);

	//GLfloat light_position[4] = { 2, -2, 3, 0};           //new
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	//glEnable(GL_COLOR_MATERIAL);
	//glColor3f(1, 1, 1);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, TEST_SPECULAR);

	
	glLightfv(GL_LIGHT1, GL_AMBIENT, TEST_AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, TEST_DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, TEST_SPECULAR);

	glLightfv(GL_LIGHT1, GL_POSITION, TEST_POSITION);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.2);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);

	glEnable(GL_LIGHT1);

	//glEnable(GL_COLOR_MATERIAL);       //new
	//glEnable(GL_COLOR);

	//glDisable(GL_LIGHTING);

	const GLfloat width = 15, height = 21, depth = 0.24;

	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, TEST_SPECULAR2);
	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef(0, 0, 0.24);
		glRectf(-0.25, -0.25, height*0.5f - 0.25, width*0.5f - 0.25);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, TEST_AMBIENT);

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR);

	glMaterialfv(GL_FRONT, GL_AMBIENT, EmeraldAmbient);        //new
	glMaterialfv(GL_FRONT, GL_DIFFUSE, EmeraldDiffuse);        //new
	glMaterialfv(GL_FRONT, GL_SPECULAR, EmeraldSpecular);      //new
	glMaterialf(GL_FRONT, GL_SHININESS, EmeraldShininess);     //new

	//glRotatef(dt * 10, 0, 0, 1);

	for (Drawable* var : toDraw) var->draw();
	

	glutSwapBuffers();
	glutPostRedisplay();
}
