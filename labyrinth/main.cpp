#include <GL/freeglut.h>
#include "mainLoop.h"

void reshapeScreen(int w, int h) {
	//window size
	int sw, sh;

	sw = w;
	sh = h;
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

	/*  GLfloat light0_specular [4] = { 1.0,1.0,1.0,1 };
	 GLfloat light0_diffuse [4] = { 0.5,0.5,0.5,1 };
	 glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
	 glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);*/


	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat light_ambient_global[4] = { 0.5,0.5,0.5,1 };          //new
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);   //new
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Labyrinth");

	initOpenGL();
	glutDisplayFunc(mainLoop);
	glutReshapeFunc(reshapeScreen);

	//glutKeyboardFunc(keyDown);
	//glutKeyboardUpFunc(keyUp);
	//glutSpecialFunc(specialKeyDown);
	//glutSpecialUpFunc(specialKeyUp);

	glutMainLoop();

	//shutdown();
	return 0;
}