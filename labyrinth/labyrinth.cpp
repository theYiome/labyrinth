#include <GL/glew.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate


bool keys[256], specialkeys[256];

void initOpenGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void handleKeys()
{
	if (keys[27]) exit(0);
}

void drawScene()
{
	glewInit();
	handleKeys();
	glm::mat4 Model = glm::mat4(1.0f);
	unsigned int l = 9;
	glGenBuffers(1, &l);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.8, 0.8, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //new

	//uklad
	glBegin(GL_LINES); //new
	 //Osie ukladu
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(1.0, 0, 0); //new
	glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(0, 1.0, 0); //new
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1.0); //new
	glEnd(); //new

	//Linie przerywane
	glEnable(GL_LINE_STIPPLE); //new
	glLineStipple(2, 0xAAAA); //new
	glBegin(GL_LINES); //new
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(-1.0, 0, 0); //new
	glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(0, -1.0, 0); //new
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, 0); glVertex3f(0, 0, -1.0); //new
	glEnd(); //new
	glDisable(GL_LINE_STIPPLE); //new


	glutSwapBuffers();
	glutPostRedisplay();
}

void reshapeScreen(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyDown(unsigned char key, int x, int y)
{
	keys[key] = true;
}
void keyUp(unsigned char key, int x, int y)
{
	keys[key] = false;
}
void specialKeyDown(int key, int x, int y)
{
	specialkeys[key] = true;
}
void specialKeyUp(int key, int x, int y)
{
	specialkeys[key] = false;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Lab01 - stage 0");

	initOpenGL();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshapeScreen);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	glutMainLoop();
	return 0;
}

