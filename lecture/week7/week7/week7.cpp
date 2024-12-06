#include<gl/glut.h>

void display(void)
{

	float shoulder = 20.0, elbow = 50.0;
	float upperleg = -55.0, lowerleg = -55.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glPushMatrix();
		glScalef(0.5, 0.5, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(1.0);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();
		// Upper Arm
		glTranslatef(0.25, 0.2, 0.0);
		glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
		glTranslatef(0.2, 0.0, 0.0);
		glPushMatrix();
			glScalef(0.4, 0.1, 1.0);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		// Lower Arm
		glTranslatef(0.2, 0.0, 0.0);
		glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
		glTranslatef(0.15, 0.0, 0.0);
		glPushMatrix();
			glScalef(0.3, 0.1, 1.0);
			glColor3f(1.0, 1.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		glLoadIdentity();
		// Upper leg
		glTranslatef(0.20, -0.25, 0.0);
		glRotatef((GLfloat)upperleg, 0.0, 0.0, 1.0);
		glTranslatef(0.15, 0.0, 0.0);
		glPushMatrix();
			glScalef(0.3, 0.1, 1.0);
			glColor3f(0.0, 1.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		// Lower leg
		glTranslatef(0.15, 0.0, 0.0);
		glRotatef((GLfloat)lowerleg, 0.0, 0.0, 1.0);
		glTranslatef(0.15, 0.0, 0.0);
		glPushMatrix();
			glScalef(0.4, 0.1, 1.0);
			glColor3f(0.0, 0.5, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		//head
		glLoadIdentity();
			glTranslatef(0.0, 0.4, 0.0);
			glTranslatef(-0.015, 0.0, 0.0);
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glutWireSphere(0.15f, 100, 100);
			glColor3f(1.0, 1.0, 1.0);
			glutSolidSphere(0.14f, 100, 100);
		glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");
	// Set Background Color
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
