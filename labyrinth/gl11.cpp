#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "materials.h"          //new

bool keys[256],specialkeys[256];

//camera
float camera_distance=3.0,camera_theta=0.2,camera_fi=1.2;
float fov=45.0;

//swiatlo
float light_theta=0.2,light_fi=1.2;

//transformacje obj.
float pos_x=0.0,pos_y=0.0,pos_z=0.0;
float scale_x=1.0,scale_y=1.0,scale_z=1.0;
float rot_x=0.0,rot_y=0.0,rot_z=0.0;

//okno
int sw,sh;

void initOpenGL()
{
glClearColor(1.0f,1.0f,1.0f,0.0f);
glEnable(GL_DEPTH_TEST);

glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
 
/*  GLfloat light0_specular [4] = { 1.0,1.0,1.0,1 };
GLfloat light0_diffuse [4] = { 0.5,0.5,0.5,1 };
glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);*/
 
 
glEnable(GL_NORMALIZE);
glEnable(GL_COLOR_MATERIAL);
 
GLfloat light_ambient_global [4] = { 0.5,0.5,0.5,1 };          //new
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_ambient_global);   //new
}

void handleKeys()
{
if (keys[27]) exit(0);
if (specialkeys[100]) camera_fi-=0.01;        //lewo
if (specialkeys[102]) camera_fi+=0.01;        //prawo
if (specialkeys[101]) camera_theta+=0.01;     //gora
if (specialkeys[103]) camera_theta-=0.01;     //dol

if (keys[113]) pos_x-=0.001; if (keys[119]) pos_x+=0.001;
if (keys[97] ) pos_y-=0.001; if (keys[115]) pos_y+=0.001;
if (keys[122]) pos_z-=0.001; if (keys[120]) pos_z+=0.001;

if (keys[101]) scale_x-=0.002; if (keys[114]) scale_x+=0.002;
if (keys[100]) scale_y-=0.002; if (keys[102]) scale_y+=0.002;
if (keys[99] ) scale_z-=0.002; if (keys[118]) scale_z+=0.002;

if (keys[116]) rot_x-=0.1; if (keys[121]) rot_x+=0.1;
if (keys[103]) rot_y-=0.1; if (keys[104]) rot_y+=0.1;
if (keys[98] ) rot_z-=0.1; if (keys[110]) rot_z+=0.1;

if (keys['i']) light_fi-=0.001;
if (keys['o']) light_fi+=0.001;
if (keys['k']) light_theta+=0.001;
if (keys['l']) light_theta-=0.001;
}

void drawScene()
{
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
					4.0*cos(light_theta)*sin(light_fi),0.0 };
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

//szescian

//transformacje
glTranslatef(pos_x, pos_y, pos_z);
glRotatef(rot_x, 1, 0, 0);
glRotatef(rot_y, 0, 1, 0);
glRotatef(rot_z, 0, 0, 1);
glScalef(scale_x, scale_y, scale_z);

glLineWidth(2.0);
glColor3f(0, 0, 0);
glBegin(GL_LINES);
glVertex3f(0.3, 0.3, 0.3); glVertex3f(0.3, 0.3, -0.3);
glVertex3f(0.3, 0.3, 0.3); glVertex3f(0.3, -0.3, 0.3);
glVertex3f(0.3, 0.3, 0.3); glVertex3f(-0.3, 0.3, 0.3);

glVertex3f(-0.3, -0.3, -0.3); glVertex3f(0.3, -0.3, -0.3);
glVertex3f(-0.3, -0.3, -0.3); glVertex3f(-0.3, 0.3, -0.3);
glVertex3f(-0.3, -0.3, -0.3); glVertex3f(-0.3, -0.3, 0.3);

glVertex3f(-0.3, 0.3, -0.3); glVertex3f(-0.3, 0.3, 0.3);
glVertex3f(-0.3, 0.3, -0.3); glVertex3f(0.3, 0.3, -0.3);
glVertex3f(-0.3, -0.3, 0.3); glVertex3f(-0.3, 0.3, 0.3);
glVertex3f(-0.3, -0.3, 0.3); glVertex3f(0.3, -0.3, 0.3);
glVertex3f(0.3, -0.3, -0.3); glVertex3f(0.3, -0.3, 0.3);
glVertex3f(0.3, -0.3, -0.3); glVertex3f(0.3, 0.3, -0.3);
glEnd();
glLineWidth(1.0);

//kolorowy tr.
glBegin(GL_TRIANGLES);
glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.3, 0.3, 0.3);
glColor3f(0.0, 1.0, 0.0); glVertex3f(0.3, -0.3, 0.3);
glColor3f(0.0, 0.0, 1.0); glVertex3f(0.3, 0.3, -0.3);
glEnd();

glEnable(GL_LIGHTING);

glPushMatrix();
glColor3f(1.0, 1.0, 0.0);
glTranslatef(-1.0, 0.0, 0.0);
glutSolidTorus(0.025, 0.25, 10, 30);
glPopMatrix();

glPushMatrix();
glColor3f(0.0, 0.0, 0.0);
glTranslatef(1.0, 0.0, 0.0);
glScalef(0.2, 0.2, 0.2);
glutSolidIcosahedron();
glPopMatrix();

glPushMatrix();
glColor3f(0.0, 1.0, 1.0);
glTranslatef(0.0, 0.5, 0.0);
glRotatef(-90.0, 1.0, 0.0, 0.0);
glutSolidCone(0.2, 0.5, 15, 3);
glPopMatrix();

glPushMatrix();
double clip_plane1[] = { -1.0,0.0,0.0,-0.10 };
double clip_plane2[] = { 1.0,0.0,0.0,0.10 };
double clip_plane3[] = { -1.0,0.0,0.0,0.10 };
double clip_plane4[] = { 1.0,0.0,0.0,-0.10 };

glTranslatef(0.0, -0.5, 0.0);

glClipPlane(GL_CLIP_PLANE1, clip_plane1);
glClipPlane(GL_CLIP_PLANE2, clip_plane2);
glClipPlane(GL_CLIP_PLANE3, clip_plane3);
glClipPlane(GL_CLIP_PLANE4, clip_plane4);

glEnable(GL_CLIP_PLANE1);
glColor3f(1.0, 0.0, 0.0); glutSolidTeapot(0.2);
glDisable(GL_CLIP_PLANE1);

glEnable(GL_CLIP_PLANE2); glEnable(GL_CLIP_PLANE3);
glColor3f(0.0, 1.0, 0.0); glutSolidTeapot(0.2);
glDisable(GL_CLIP_PLANE2); glDisable(GL_CLIP_PLANE3);

glEnable(GL_CLIP_PLANE4);
glColor3f(0.0, 0.0, 1.0); glutSolidTeapot(0.2);
glDisable(GL_CLIP_PLANE4);
glPopMatrix();

glDisable(GL_COLOR_MATERIAL);       //new
glPushMatrix();
glMaterialfv(GL_FRONT, GL_AMBIENT, PolishedGoldAmbient);        //new
glMaterialfv(GL_FRONT, GL_DIFFUSE, PolishedGoldDiffuse);        //new
glMaterialfv(GL_FRONT, GL_SPECULAR, PolishedGoldSpecular);      //new
glMaterialf(GL_FRONT, GL_SHININESS, PolishedGoldShininess);     //new
//glMaterialf(GL_FRONT,GL_SHININESS,100);
glTranslatef(0.0, 0.0, 0.8);
glutSolidSphere(0.2, 32, 32);
glPopMatrix();
glEnable(GL_COLOR_MATERIAL);       //new

glPushMatrix();
glColor3f(0.0, 0.0, 1.0);
glTranslatef(0.0, 0.0, -0.8);
glutSolidSphere(0.2, 10, 10);
glPopMatrix();

glutSwapBuffers();
glutPostRedisplay();
}

void reshapeScreen(int w, int h)
{
sw=w;
sh=h;
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0f,(GLfloat)w/(GLfloat)h, 0.1f,100.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void keyDown(unsigned char key, int x,int y)
{
keys[key]=true;

if (key==48)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-1.5*(GLfloat)sw/(GLfloat)sh,1.5*(GLfloat)sw/(GLfloat)sh,-1.5,1.5,-3.0,12.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
if (key==91) fov-=1.0;
if (key==93) fov+=1.0;
if (key==57 || key==91 || key==93)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(fov,(GLfloat)sw/(GLfloat)sh, 0.1f,100.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

}
void keyUp(unsigned char key, int x,int y)
{
keys[key]=false;
}
void specialKeyDown(int key, int x, int y)
{
specialkeys[key]=true;
}
void specialKeyUp(int key, int x, int y)
{
specialkeys[key]=false;
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(640,480);
glutInitWindowPosition(0,0);

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

