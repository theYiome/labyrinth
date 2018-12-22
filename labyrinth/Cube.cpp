#include "Cube.h"
#include "GL/freeglut.h"

Cube::Cube() {
	position.x = position.y = position.z = 0;
	velocity.x = velocity.y = velocity.z = 0;
	color.r = color.g = color.b = 0;
	
	velocity.x = 0.4;
	color.b = 0.5;
	size = 0.5;
}

void Cube::draw() {
	glColor3f(color.r, color.g, color.b);

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutSolidCube(size);
	glPopMatrix();
}

void Cube::update(GLfloat dt) {
	position = position + (velocity*dt);
}
