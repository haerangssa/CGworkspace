#include <iostream>
#include <gl/glut.h> 
#include <gl/glu.h>
using namespace std;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3f(1, 0, 0);
	glutWireTeapot(3);
	glColor3f(0, 1, 0);
	glTranslatef(10, 0, -5);
	glutWireTeapot(3);
	glColor3f(0, 0, 1);
	glTranslatef(-20, 0, -5);
	glutWireTeapot(3);
	glFlush();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 30.0);
	// 1. -30.0, 30.0, -15.0, 15.0, 5.0, 30.0
	// 2. -5.0, 5.0, -15.0, 15.0, 5.0, 30.0
	// 3. -12.0, 12.0, -6.0, 6.0, 5.0, 30.0
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Viewing Transformation");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}