/*#include <iostream>
#include <gl/glut.h>
#include <gl/glu.h>
using namespace std;

#define WIDTH 600
#define HEIGHT 400

void init()
{
	glutInitWindowPosition(100, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);
	glColor3f(1, 0, 0);
	glTranslatef(10, 5, 10);
	glutWireTeapot(3);
	glColor3f(0, 1, 0);
	glTranslatef(-10, -5, -5);
	glutWireTeapot(3);
	glColor3f(0, 0, 1);
	glTranslatef(-10, -5, 15);
	glutWireTeapot(3);
	glFlush();
}
void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, h / 2, w / 2, h / 2);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("ViewingTransformation");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
*/
#include <iostream>
#include <gl/glut.h> 
#include <gl/glu.h>
using namespace std;

#define WIDTH 600
#define HEIGHT 400

void init()
{
	glutInitWindowPosition(100, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);

	// Red Teapot
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(10, 5, 10);
	glutWireTeapot(3);
	glPopMatrix();

	// Green Teapot
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, 0, 5);
	glutWireTeapot(3);
	glPopMatrix();

	// Blue Teapot
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(-10, -5, 20);
	glutWireTeapot(3);
	glPopMatrix();

	glFlush();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, 0.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, h / 2, w / 2, h / 2);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("3D Teapot Placement");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}