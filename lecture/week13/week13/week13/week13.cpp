#include <iostream>
#include <math.h>
#include <gl/glut.h>
using namespace std;
#define WIDTH 600
#define HEIGHT 600
GLfloat ambient[] = { 1.0, 0, 0, 1.0 };
GLfloat diffuse[] = { 1.0, 0, 1.0, 1.0 };
GLfloat specular[] = { 0, 0, 1.0, 1.0 };
float spin = 0;
void display()
{
	GLfloat position[] = { 0, 0, 2, 1 };
	glClear(GL_COLOR_BUFFER_BIT
		| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// View Volume
	glOrtho(-1, 1, -1, 1, 1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(spin += 0.3, 1, 0, 0);
	// Light Position
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glPopMatrix();
	// Camera
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
	// Light Type
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	// Teapot
	glColor3f(1, 0, 1);
	glutSolidTeapot(0.3);
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA
		| GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("test");
	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}

/*quiz2
#include <iostream>
#include <math.h>
#include <gl/glut.h>
using namespace std;
#define WIDTH 600
#define HEIGHT 600
GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0, 0.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_a[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat_d[] = { 1, 0.2, 1.0, 1.0 }; // violet 조명 
GLfloat mat_s[] = { 0.1, 0.5, 1.0, 1.0 }; // skyblue 하이라이트
GLfloat low_sh[] = { 100 };
GLfloat material_emission[] = { 0,0.5,0,1 };
GLfloat position[] = { 0, 0, 2, 1 };
bool dir = true;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT
		| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// View Volume
	glOrtho(-1, 1, -1, 1, 1, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Light Position
	if (dir) position[0] += 0.005;
	else position[0] -= 0.005;
	if (position[0] >= 5.0) dir = false;
	if (position[0] <= -5.0) dir = true;
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	// Camera
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
	// Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	// Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
	glMaterialfv(GL_FRONT_AND_BACK,
		GL_EMISSION, material_emission);
	// Teapot
	glColor3f(1, 0, 1);
	glutSolidTeapot(0.3);
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA
		| GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("test");
	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
*/