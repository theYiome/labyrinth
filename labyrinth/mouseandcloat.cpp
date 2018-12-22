#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "GLM/glm.hpp"
#include "materials.h"          

bool keys[256], specialkeys[256];

//camera
float camera_distance = 3.0, camera_theta = 0.2, camera_fi = 1.2;
float fov = 45.0;

//swiatlo
float light_theta = 1.2, light_fi = 1.2;

//transformacje obj.
float pos_x = 0.0, pos_y = 0.0, pos_z = 0.0;
float scale_x = 1.0, scale_y = 1.0, scale_z = 1.0;
float rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;

//okno
int sw, sh;

//mysz
int mouse_button, mouse_x, mouse_y;

float flag = 0.0;     //new  

void initOpenGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	GLfloat light0_specular [4] = { 1.0,1.0,1.0,1 };
	GLfloat light0_diffuse [4] = { 0.5,0.5,0.5,1 };
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);


	glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);

	GLfloat light_ambient_global[4] = { 0.5, 0.5, 0.5, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);
}

void handleKeys()
{
	if (keys[27]) exit(0);
	if (specialkeys[100]) camera_fi -= 0.001;        //lewo
	if (specialkeys[102]) camera_fi += 0.001;        //prawo
	if (specialkeys[101]) camera_theta += 0.001;     //gora
	if (specialkeys[103]) camera_theta -= 0.001;     //dol

	if (keys[113]) pos_x -= 0.001; if (keys[119]) pos_x += 0.001;
	if (keys[97]) pos_y -= 0.001; if (keys[115]) pos_y += 0.001;
	if (keys[122]) pos_z -= 0.001; if (keys[120]) pos_z += 0.001;

	if (keys[101]) scale_x -= 0.002; if (keys[114]) scale_x += 0.002;
	if (keys[100]) scale_y -= 0.002; if (keys[102]) scale_y += 0.002;
	if (keys[99]) scale_z -= 0.002; if (keys[118]) scale_z += 0.002;

	if (keys[116]) rot_x -= 0.1; if (keys[121]) rot_x += 0.1;
	if (keys[103]) rot_y -= 0.1; if (keys[104]) rot_y += 0.1;
	if (keys[98]) rot_z -= 0.1; if (keys[110]) rot_z += 0.1;

	if (keys['i']) light_fi -= 0.001;
	if (keys['o']) light_fi += 0.001;
	if (keys['k']) light_theta += 0.001;
	if (keys['l']) light_theta -= 0.001;
}

void cross_product(float u[3], float v[3], float *res)
{
	res[0] = u[1] * v[2] - u[2] * v[1];
	res[1] = u[2] * v[0] - u[0] * v[2];
	res[2] = u[0] * v[1] - u[1] * v[0];
}

void drawScene()
{
	int x, y;
	float fx, fy, u[3], v[3], res[3], res1[3], res2[3], res3[3], res4[3];
	float flag_x[20][20], flag_y[20][20], flag_z[20][20];
	float flag_nx[20][20], flag_ny[20][20], flag_nz[20][20];

	handleKeys();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(camera_distance*cos(camera_theta)*cos(camera_fi),
		camera_distance*sin(camera_theta),
		camera_distance*cos(camera_theta)*sin(camera_fi),
		0.0, 0.0, 0.0,
		camera_distance*cos(camera_theta + 0.1)*cos(camera_fi),
		camera_distance*sin(camera_theta + 0.1),
		camera_distance*cos(camera_theta + 0.1)*sin(camera_fi));

	GLfloat light0_position[4] = { 4.0*cos(light_theta)*cos(light_fi),
		4.0*sin(light_theta),
		4.0*cos(light_theta)*sin(light_fi), 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glDisable(GL_LIGHTING);

	//uklad
	glBegin(GL_LINES);
	//Osie ukladu
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(1.0, 0, 0);
	glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(0, 1.0, 0);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1.0);
	glEnd();

	//Linie przerywane
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0xAAAA);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(-1.0, 0, 0);
	glColor3f(0.0, 1.0, 0.0); glVertex3f(0, 0, 0); glVertex3f(0, -1.0, 0);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, 0); glVertex3f(0, 0, -1.0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glEnable(GL_LIGHTING);

	//transformacje
	glTranslatef(pos_x, pos_y, pos_z);
	glRotatef(rot_x, 1, 0, 0);
	glRotatef(rot_y, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);
	glScalef(scale_x, scale_y, scale_z);


	glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);
	// flag=flag+0.0001;
	for (x = 0; x < 20; x++)
		for (y = 0; y < 20; y++)
		{
			flag_x[x][y] = (x - 10)*0.1;
			flag_y[x][y] = 0.2*sin((x - 10)*0.2 - flag)*cos((y - 10)*0.2 + flag);
			flag_z[x][y] = (y - 10)*0.1;
		}
	for (x = 1; x < 19; x++)
		for (y = 1; y < 19; y++)
		{
			u[0] = flag_x[x][y + 1] - flag_x[x][y];
			u[1] = flag_y[x][y + 1] - flag_y[x][y];
			u[2] = flag_z[x][y + 1] - flag_z[x][y];

			v[0] = flag_x[x + 1][y] - flag_x[x][y];
			v[1] = flag_y[x + 1][y] - flag_y[x][y];
			v[2] = flag_z[x + 1][y] - flag_z[x][y];

			cross_product(u, v, res1);
			
			u[0] = flag_x[x + 1][y] - flag_x[x][y];
			u[1] = flag_y[x + 1][y] - flag_y[x][y];
			u[2] = flag_z[x + 1][y] - flag_z[x][y];

			v[0] = flag_x[x][y - 1] - flag_x[x][y];
			v[1] = flag_y[x][y - 1] - flag_y[x][y];
			v[2] = flag_z[x][y - 1] - flag_z[x][y];

			cross_product(u, v, res2);

			u[0] = flag_x[x][y - 1] - flag_x[x][y];
			u[1] = flag_y[x][y - 1] - flag_y[x][y];
			u[2] = flag_z[x][y - 1] - flag_z[x][y];

			v[0] = flag_x[x - 1][y] - flag_x[x][y];
			v[1] = flag_y[x - 1][y] - flag_y[x][y];
			v[2] = flag_z[x - 1][y] - flag_z[x][y];

			cross_product(u, v, res3);

			u[0] = flag_x[x - 1][y] - flag_x[x][y];
			u[1] = flag_y[x - 1][y] - flag_y[x][y];
			u[2] = flag_z[x - 1][y] - flag_z[x][y];

			v[0] = flag_x[x][y + 1] - flag_x[x][y];
			v[1] = flag_y[x][y + 1] - flag_y[x][y];
			v[2] = flag_z[x][y + 1] - flag_z[x][y];

			cross_product(u, v, res4);

			flag_nx[x][y] = (res1[0] + res2[0] + res3[0] + res4[0]);
			flag_ny[x][y] = (res1[1] + res2[1] + res3[1] + res4[1]);
			flag_nz[x][y] = (res1[2] + res2[2] + res3[2] + res4[2]);
		}

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (x = 1; x < 18; x++)
		for (y = 1; y < 18; y++)
		{
			glNormal3f(flag_nx[x][y], flag_ny[x][y], flag_nz[x][y]);
			glVertex3f(flag_x[x][y], flag_y[x][y], flag_z[x][y]);

			glNormal3f(flag_nx[x + 1][y], flag_ny[x + 1][y], flag_nz[x + 1][y]);
			glVertex3f(flag_x[x + 1][y], flag_y[x + 1][y], flag_z[x + 1][y]);

			glNormal3f(flag_nx[x + 1][y + 1], flag_ny[x + 1][y + 1], flag_nz[x + 1][y + 1]);
			glVertex3f(flag_x[x + 1][y + 1], flag_y[x + 1][y + 1], flag_z[x + 1][y + 1]);

			glNormal3f(flag_nx[x][y + 1], flag_ny[x][y + 1], flag_nz[x][y + 1]);
			glVertex3f(flag_x[x][y + 1], flag_y[x][y + 1], flag_z[x][y + 1]);
		}
	glEnd();

	
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	for (x=1;x<19;x++)
	for (y=1;y<19;y++)
	{
		glVertex3f(flag_x[x][y],flag_y[x][y],flag_z[x][y]);
		glVertex3f(flag_x[x][y]+flag_nx[x][y],flag_y[x][y]+flag_ny[x][y],flag_z[x][y]+flag_nz[x][y]);
	}
	glEnd();
	glEnable(GL_LIGHTING);
	

	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glBlendEquation(GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);

	glBlendEquation(GL_FUNC_SUBTRACT);
	glBlendFunc(GL_SRC_COLOR,GL_SRC_ALPHA);

	glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
	glBlendFunc(GL_SRC_COLOR,GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glColor4f(1.0, 0.0, 0.0, 0.5); glVertex3f(-0.5, 0.5, 1.0);
	glColor4f(0.0, 1.0, 0.0, 0.9); glVertex3f(0.5, 0.5, 1.0);
	glColor4f(0.0, 0.0, 1.0, 0.5); glVertex3f(0.5, -0.5, 1.0);
	glColor4f(0.0, 0.0, 0.0, 0.5); glVertex3f(-0.5, -0.5, 1.0);
	glEnd();


	glEnable(GL_COLOR_LOGIC_OP);
	glBlendEquation(GL_LOGIC_OP);
	glLogicOp(GL_INVERT);

	glBegin(GL_QUADS);
	glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-0.5,0.5,1.0);
	glColor4f(0.0,0.0,0.0,1.0); glVertex3f(0.5,0.5,1.0);
	glColor4f(0.0,0.0,0.0,1.0); glVertex3f(0.5,-0.5,1.0);
	glColor4f(0.0,0.0,0.0,1.0); glVertex3f(-0.5,-0.5,1.0);
	glEnd();
	glDisable(GL_COLOR_LOGIC_OP);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);


	glutSwapBuffers();
	glutPostRedisplay();
}

void reshapeScreen(int w, int h)
{
	sw = w;
	sh = h;
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

	if (key == 48)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1.5*(GLfloat)sw / (GLfloat)sh, 1.5*(GLfloat)sw / (GLfloat)sh, -1.5, 1.5, -3.0, 12.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	if (key == 91) fov -= 1.0;
	if (key == 93) fov += 1.0;
	if (key == 57 || key == 91 || key == 93)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov, (GLfloat)sw / (GLfloat)sh, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

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

void mouseButton(int button, int state, int x, int y)
{
	mouse_button = -1;
	if (button == GLUT_LEFT_BUTTON)
	{
		mouse_button = button;
		if (state == GLUT_DOWN)
		{
			mouse_x = x;
			mouse_y = y;
		}
	}
}

void mouseMotion(int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON)
	{
		camera_fi += 2.0 / glutGet(GLUT_WINDOW_WIDTH)*(x - mouse_x);
		camera_theta -= 2.0 / glutGet(GLUT_WINDOW_HEIGHT)*(mouse_y - y);
		mouse_x = x;
		mouse_y = y;
		glutPostRedisplay();
	}
}

void timerFunction(int param)
{
	flag += 0.01;
	//printf("\n%lf",flag);
	glutTimerFunc(10, timerFunction, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("GLUT GLEW APP");

	initOpenGL();

	glewInit();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshapeScreen);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	glutTimerFunc(10, timerFunction, 0);

	glutMainLoop();
	return 0;
}

