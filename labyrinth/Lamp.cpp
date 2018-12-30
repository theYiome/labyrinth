#include "Lamp.h"
#include <iostream>

const std::array<int, Lamp::MAX_LIGHTS> Lamp::LIGHTS_ENUM = { GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

int Lamp::lightAvailable[Lamp::MAX_LIGHTS] = { true, true, true, true, true, true, true };


const int Lamp::getFirstAvailableID() {
	int newID = 0;
	while (lightAvailable[newID] == false) newID++;
	lightAvailable[newID] = false;
	return newID;
}

void Lamp::draw(void) {
	glLightfv(LIGHTS_ENUM[ID], GL_DIFFUSE, DIFFUSE);

	const GLfloat NO_LIGHT[4] = { 0, 0, 0, 0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, DIFFUSE);

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutWireTorus(0.05, 0.2, 32, 32);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NO_LIGHT);
}


void Lamp::move(GLfloat dt) {
	//base class move(dt)
	Movable::move(dt);


	//expanded to move light source as well
	if (ID != NO_RESOURCE) {
		const GLfloat TEMP_POS[4] = { position.x, position.y, position.z, 1 };
		glLightfv(LIGHTS_ENUM[ID], GL_POSITION, TEMP_POS);
	}
}

Lamp::Lamp() : ID(getFirstAvailableID()) {
	speedFactor = 0.8f;

	if (ID != NO_RESOURCE) {
		glEnable(LIGHTS_ENUM[ID]);

		glLightfv(LIGHTS_ENUM[ID], GL_AMBIENT, AMBIENT);
		glLightfv(LIGHTS_ENUM[ID], GL_DIFFUSE, DIFFUSE);
		glLightfv(LIGHTS_ENUM[ID], GL_SPECULAR, SPECULAR);

		const GLfloat TEMP_POS[4] = { position.x, position.y, position.z, 1 };
		glLightfv(LIGHTS_ENUM[ID], GL_POSITION, TEMP_POS);

		glLightf(LIGHTS_ENUM[ID], GL_CONSTANT_ATTENUATION, 0.05);
		glLightf(LIGHTS_ENUM[ID], GL_LINEAR_ATTENUATION, 0.2);
		glLightf(LIGHTS_ENUM[ID], GL_QUADRATIC_ATTENUATION, 0.2);
		std::cout << "USING GL_LIGHT" << ID + 1 << std::endl;
	} else std::cout << "NO MORE LIGHTS AVAILABLE" << std::endl;

}

Lamp::Lamp(Lamp &toCopy) {
	ID = toCopy.ID;
	toCopy.ID = NO_RESOURCE;
}

Lamp::~Lamp() {
	if(ID != NO_RESOURCE) {
		lightAvailable[ID] = true;
		glDisable(LIGHTS_ENUM[ID]);
	}
}