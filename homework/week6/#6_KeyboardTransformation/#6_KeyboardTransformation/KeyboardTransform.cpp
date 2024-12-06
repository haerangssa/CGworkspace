#include <gl/glut.h> 
#include <iostream>
#include <math.h> //sin(),cos()
using namespace std;

#define PI 3.141592

void drawBox()
{
	// Red rectangle
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	// Green rectangle
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	// Blue lines
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	glPushMatrix();		   // initial setup: no accumulation
	glRotatef(45.0, 1.0, 1.0, 1.0);    // 2. 1,1,1 축을 중심으로 45도 기울이기
	glScalef(0.1, 0.2, 0.1); // 1. y쪽 크기를 키움
	drawBox(); // 1,2번 없으면 앞면밖에 보이지 않음.
	glPopMatrix();
	glFlush();
}

void xyzRotate(char mode)
{
	switch (mode) {
	case 'x': glRotatef(PI, 1, 0, 0); break;
	case 'y': glRotatef(PI, 0, 1, 0); break;
	case 'z': glRotatef(PI, 0, 0, 1); break;
	default: break;
	}
}
void xyzScale(char mode) {
	switch (mode) {
	case 's': glScalef(1.05, 1.05, 1.05); break;
	case 'a': glScalef(0.95, 0.95, 0.95); break;
	default: break;
	}
}
void xyzTranslate(char mode) {
	switch (mode) {
	case 't': glTranslatef(0.05, 0.0, 0.0); break;
	case 'r': glTranslatef(-0.05, 0.0, 0.0); break;
	default: break;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x': xyzRotate('x'); glutPostRedisplay(); break;
	case 'y': xyzRotate('y'); glutPostRedisplay(); break;
	case 'z': xyzRotate('z'); glutPostRedisplay(); break;
	case 's': xyzScale('s'); glutPostRedisplay(); break;
	case 'a': xyzScale('a'); glutPostRedisplay(); break;
	case 't': xyzTranslate('t'); glutPostRedisplay(); break;
	case 'r': xyzTranslate('r'); glutPostRedisplay(); break;
	default: break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");

	// Set Background Color
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}