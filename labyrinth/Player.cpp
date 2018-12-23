#include "Player.h"

Player::Player() {
	squarePosition.x = squarePosition.y = 1;

	position.x = position.y = 0.5f;
	position.z = 0.5f;
	velocity.x = velocity.y = velocity.z = 0;
}

void Player::draw(void) {
	glColor3f(0, 0.6, 0);

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutSolidSphere(0.2, 64, 64);
	glPopMatrix();
}

void Player::update(GLfloat dt) {
	position = position + (velocity*dt);
	velocity -= velocity * dt;

}
