
#include <iostream>
#include <gl/glut.h>
using namespace std;
#define WIDTH 600
#define HEIGHT 600
float spin = 0;
void display()
{
	GLfloat position[] = { 0, 0, -1, 0 };
	glLoadIdentity();
	// Orthographic View Volume
	glClear(GL_COLOR_BUFFER_BIT
		| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1, 1, -1, 1, 1, 30);
	glViewport(0, 0, WIDTH, HEIGHT);
	// Camera Position, Direction, Up vector
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.7, 0.7, 1.0); // ��ü ũ�� ���̱�
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0); //camera
	// LIGHT Rotation
	glPushMatrix();
	glTranslatef(0.3, 0, 0);
	glRotatef(spin, 0.0, 0.5, 0.0);
	spin += 0.3;
	// ȸ�� �ӵ� ����
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	// Skyblue LIGHT Cube Display
	glTranslatef(position[0], position[1], position[2]);
	glDisable(GL_LIGHTING);
	glColor3f(0, 1, 1);
	glutWireCube(0.1);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	// Draw Solid Torus
	glTranslatef(0.3, 0, 0);
	glColor3f(1, 0, 1);
	glutSolidTorus(0.1, 0.3, 100, 100);
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH
		| GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("test");
	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

