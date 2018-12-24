#include <GL/freeglut.h>
#include "mainLoop.h"

void reshapeScreen(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initOpenGL() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat light_ambient_global[4] = { 0.5,0.5,0.5,1 };          //new
	GLfloat light0_specular[4] = { 1.0,1.0,1.0,1 };
	GLfloat light0_diffuse[4] = { 0.5,0.5,0.5,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);   //new
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

}

void inputHandler(unsigned char key, int x, int y) {
	
	if (currentScene->getThingIn(currentScene->player.squarePosition.x, currentScene->player.squarePosition.y) == '!') {
		//GG WON
		exit(0);
	}


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
			currentScene->getCamera().desiredHeight++;
		break;

		case '2':
			currentScene->getCamera().desiredHeight--;
		break;

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//Initalize with multisampling for extra smoothnes
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);

	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Labyrinth");

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