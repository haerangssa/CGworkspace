*#include <gl/glut.h>

GLfloat blueAngle = 0.0f;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f); // red
	glutSolidSphere(0.1f, 100, 100);

	glPushMatrix(); // 1. 0.0
	glTranslatef(0.6f, 0.0f, 0.0f); // 2. 블루 이동
	glColor3f(0.0f, 0.0f, 1.0f); // blue 
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix(); // 3. 블루 시점 이동
	glTranslatef(0.3f, 0.0f, 0.0f);// 4. 그린 이동
	glColor3f(0.0f, 1.0f, 0.0f); // green
	glutSolidSphere(0.05f, 100, 100);

	glPopMatrix(); // pop green translate 3. 그린 이동 삭제
	glPopMatrix(); // pop blue translate 2. 블루 이동 삭제 >> 1. 레드 0.0
	glTranslatef(0.8f, 0.0f, 0.0f); 2. 옐로 이동
	glColor3f(1.0f, 1.0f, 0.0f); // yellow
	glutSolidSphere(0.08f, 100, 100);

	glPushMatrix(); // 3. 옐로 시점 이동
	glRotatef(1 - blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-0.2f, 0.0f, 0.0f); // 4. 핑크 이동
	glColor3f(1.0f, 0.0f, 1.0f); // pink
	glutSolidSphere(0.04f, 100, 100);
	glPopMatrix(); // 3. 핑크 이동 삭제

	blueAngle += 1.0f;
	if (blueAngle == 360) blueAngle = 0;
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

