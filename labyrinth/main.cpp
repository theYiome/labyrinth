#include <GL/glew.h>
#include <GL/freeglut.h>
#include "gameLoop.h"

void reshapeScreen(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
Global ambient light source parameters
*/
static const GLfloat GLOBAL_AMBIENT_LIGHT[4] = { 0.1, 0.1, 0.1, 1 };

void initOpenGL() {

	glClearColor(0, 0, 0, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR);
	glEnable(GL_COLOR_MATERIAL);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GLOBAL_AMBIENT_LIGHT);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void inputHandler(unsigned char key, int x, int y) {

	if (currentScene == nullptr) return;

	if (currentScene->getThingIn(currentScene->player.squarePosition.x, currentScene->player.squarePosition.y) == '!') {
		//GG WON
		exit(0);
	}

	const GLfloat verticalSpeed = 0.33;
	


	switch (key) {
		case 'a':
			if (currentScene->getThingIn(currentScene->player.squarePosition.x, currentScene->player.squarePosition.y - 1) != '#')
				currentScene->player.squarePosition.y--;
		break;

		case 'd':
			if (currentScene->getThingIn(currentScene->player.squarePosition.x, currentScene->player.squarePosition.y + 1) != '#')
				currentScene->player.squarePosition.y++;
		break;

		case 'w':
			if (currentScene->getThingIn(currentScene->player.squarePosition.x - 1, currentScene->player.squarePosition.y) != '#')
				currentScene->player.squarePosition.x--;
		break;

		case 's':
			if(currentScene->getThingIn(currentScene->player.squarePosition.x + 1, currentScene->player.squarePosition.y) != '#')
				currentScene->player.squarePosition.x++;
		break;

		case '1':
			currentScene->getCamera().targetPosition.z += verticalSpeed;
		break;

		case '2':
			currentScene->getCamera().targetPosition.z -= verticalSpeed;
		break;

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//Initalize with multisampling for extra smoothnes
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_ALPHA);
	glEnable(GLUT_MULTISAMPLE);

	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Labyrinth");

	if (glewInit() != GLEW_OK) return -2;

	initOpenGL();
	glutDisplayFunc(mainLoop);
	glutReshapeFunc(reshapeScreen);
	glutCloseFunc(shutdown);

	//glutKeyboardFunc(keyDown);
	glutKeyboardFunc(inputHandler);
	//glutSpecialFunc(specialKeyDown);
	//glutSpecialUpFunc(specialKeyUp);

	glutMainLoop();

	return 0;
}