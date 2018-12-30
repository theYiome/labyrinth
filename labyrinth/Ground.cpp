#include "Ground.h"

void Ground::draw(void) {
	glColor3f(0.4, 0.4, 0.4);

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			glPushMatrix();
				glTranslatef(xOffset + h * tileSize, yOffset + w * tileSize, zOffset);
				glRectf(0, 0, tileSize, tileSize);
			glPopMatrix();
		}
	}
}

Ground::Ground(int  w, int h) : width(w), height(h) {
	xOffset = -0.25;
	yOffset = -0.25;
	zOffset = 0.25;

	tileSize = 0.5f;
}
