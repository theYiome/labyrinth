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

void inputHandler(int key, int x, int y) {

	if (currentScene == nullptr) return;

	const GLfloat verticalSpeed = 0.4;

	switch (key) {
		case GLUT_KEY_LEFT:
			if (currentScene->getThingIn(currentScene->player.squarePosition.x, currentScene->player.squarePosition.y - 1) != '#')
				currentScene->player.squarePosition.y--;
		break;

		case GLUT_KEY_RIGHT:
			if (currentScene->getThingIn(currentScene->player.squarePosition.x, currentScene->player.squarePosition.y + 1) != '#')
				currentScene->player.squarePosition.y++;
		break;

		case GLUT_KEY_UP:
			if (currentScene->getThingIn(currentScene->player.squarePosition.x - 1, currentScene->player.squarePosition.y) != '#')
				currentScene->player.squarePosition.x--;
		break;

		case GLUT_KEY_DOWN:
			if(currentScene->getThingIn(currentScene->player.squarePosition.x + 1, currentScene->player.squarePosition.y) != '#')
				currentScene->player.squarePosition.x++;
		break;

		case GLUT_KEY_F1:
			currentScene->getCamera().targetPosition.z += verticalSpeed;
		break;

		case GLUT_KEY_F2:
			currentScene->getCamera().targetPosition.z -= verticalSpeed;
		break;

		case GLUT_KEY_F11:
			glutFullScreenToggle();
		break;

		case GLUT_KEY_F12:
			glutDestroyWindow(glutGetWindow());
		break;

	}

	char currentPlace = currentScene->getThingIn(currentScene->player.squarePosition.x, currentScene->player.squarePosition.y);
	if (currentPlace == '!') {
		nextScene = true;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//Initalize with multisampling for extra smoothnes
	glutSetOption(GLUT_MULTISAMPLE, 16);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_ALPHA);
	
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Labyrinth");

	if (glewInit() != GLEW_OK) return -2;

	initOpenGL();
	glutDisplayFunc(mainLoop);
	glutReshapeFunc(reshapeScreen);
	glutCloseFunc(shutdown);

	glutSpecialFunc(inputHandler);
	glutFullScreenToggle();

	glutMainLoop();

	return 0;
}