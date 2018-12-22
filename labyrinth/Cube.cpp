#include "Cube.h"
#include "GL/freeglut.h"

Cube::Cube(GLfloat xPos, GLfloat yPos) {
	position.x = position.y = position.z = 0;
	velocity.x = velocity.y = velocity.z = 0;
	color.r = color.g = color.b = 0;
	
	color.b = 1;

	velocity.z = -0.3;
	velocity.y = -0.2;
	velocity.x = -0.3;

	position.x = xPos;
	position.y = yPos;
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
