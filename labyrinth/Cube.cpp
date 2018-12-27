#include "Cube.h"
#include "GL/freeglut.h"

Cube::Cube(int xPlace, int yPlace) {
	position.x = position.y = position.z = 0;
	color.r = color.g = color.b = .8f;

	position.x = xPlace * 0.5f;
	position.y = yPlace * 0.5f;

	position.z = 0.5f;
}

void Cube::draw() {
	glColor3f(color.r, color.g, color.b);

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutSolidCube(size);
	glPopMatrix();
}