#include "Cube.h"
#include "GL/freeglut.h"

Cube::Cube() {
}


Cube::~Cube() {
}

void Cube::draw() {
	glColor3f(0.5, 0, 0);

	glPushMatrix();
		glTranslatef(0.5, 0, 0);
		glutSolidCube(0.5f);
	glPopMatrix();
}
