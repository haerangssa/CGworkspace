#include <gl/glut.h>

GLfloat blueAngle = 0.0f;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f); // red
	glutSolidSphere(0.1f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.6f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);	// blue
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);	// green
	glutSolidSphere(0.05f, 100, 100);
	
	glPushMatrix(); // 그린 기준 설정
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.1f, 0.0f, 0.0f); // 스카이블루 이동
	glColor3f(0.0f, 1.0f, 1.0f); // skyblue
	glutSolidSphere(0.015f, 100, 100);
	glPopMatrix(); // 스카이블루 이동 삭제
	
	glPopMatrix(); // 그린 기준 설정 삭제
	glRotatef(-2*blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.15f, 0.0f, 0.0f); // 블랙 이동
	glColor3f(0.0f, 0.0f, 0.0f); // black
	glutSolidSphere(0.025f, 100, 100);
	glPopMatrix(); // 블랙 이동 삭제

	glPopMatrix(); // 블루기준 삭제 >> 레드
	glPushMatrix(); // 옐로 기준 설정
	glRotatef(1-blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f); // 옐로 이동
	glColor3f(1.0f, 1.0f, 0.0f); // yellow
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix(); // 옐로 기준 설정
	glRotatef(1-blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.1f, 0.0f, 0.0f); // 핑크 이동
	glColor3f(1.0f, 0.0f, 0.5f); // pink
	glutSolidSphere(0.025f, 100, 100);
	glPopMatrix(); // 핑크 이동 삭제

	glPopMatrix(); // 옐로 기준 삭제 >> 레드
	
	blueAngle += 0.5f;
	if (blueAngle == 360) blueAngle = 0;
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;
}
