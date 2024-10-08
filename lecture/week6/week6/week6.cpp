/*#include <gl/glut.h>

GLfloat blueAngle = 0.0f;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);// red
	glutSolidSphere(0.1f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f); //translate 다음에 rotate해야함.
	glTranslatef(0.6f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);// blue
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);// green
	glutSolidSphere(0.05f, 100, 100);
	glPopMatrix();
	glPopMatrix();

	blueAngle += 1.0f; // rotate 1도, 2도, 3도 계속 돌게됨
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);

	glutCreateWindow("Transformation");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}
*/

//퀴즈2, 2 이어 하기
#include <gl/glut.h>

GLfloat blueAngle = 0.0f;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f); // red
	glutSolidSphere(0.1f, 100, 100);

	glPushMatrix();
	glTranslatef(0.6f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix();
	glTranslatef(0.3f, 0.0f, 0.0f);// 블루 기준
	glColor3f(0.0f, 1.0f, 0.0f); // green
	glutSolidSphere(0.05f, 100, 100);

	glPopMatrix(); // pop green translate 
	glPopMatrix(); // pop blue translate
	glTranslatef(0.8f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f); // yellow
	glutSolidSphere(0.08f, 100, 100);

	glPushMatrix();
	glRotatef(1-blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-0.2f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f); // pink
	glutSolidSphere(0.04f, 100, 100);
	glPopMatrix();

	blueAngle += 1.0f;
	if (blueAngle == 360) blueAngle = 0;
	glFlush();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);

	glutCreateWindow("Transformation");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}
