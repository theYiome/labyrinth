#include "Player.h"

Player::Player() {
	squarePosition.x = squarePosition.y = 1;
	targetPosition.z = 0.5f;
	speedFactor = 16;
}

void Player::draw(void) {
	glColor3f(0.8, 0, 0);

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutSolidSphere(0.2, 64, 64);
	glPopMatrix();
}