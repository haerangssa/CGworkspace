#include <gl/glut.h>

GLfloat blueAngle = 0.0f;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f); // red
	glutSolidSphere(0.1f, 100, 100);

	glPushMatrix(); // ���� ���� 0.0
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.6f, 0.0f, 0.0f); // ��� �̵�
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix(); // ��� ���� ����
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f); // �׸� �̵�
	glColor3f(0.0f, 1.0f, 0.0f);  // green
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix(); // �׸� ���� ����
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.1f, 0.0f, 0.0f); // ��ī�̺�� �̵�
	glColor3f(0.0f, 1.0f, 1.0f); // skyblue
	glutSolidSphere(0.015f, 100, 100);
	glPopMatrix(); // ��ī�̺�� �̵� ����

	glPopMatrix(); // �׸� ���� ���� ����
	glPushMatrix(); //  ��� ���� �缳��
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.15f, 0.0f, 0.0f); // �� �̵�
	glColor3f(0.5f, 0.0f, 0.0f); // black
	glutSolidSphere(0.025f, 100, 100);
	glPopMatrix(); // �� �̵� ����

	glPopMatrix(); // ������ ���� >> ����
	glPushMatrix(); // ���� ���� ����
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f); // ���� �̵�
	glColor3f(1.0f, 1.0f, 0.0f); // yellow
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix(); // ���� ���� ����
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.1f, 0.0f, 0.0f); // ��ũ �̵�
	glColor3f(1.0f, 0.0f, 0.5f); // pink
	glutSolidSphere(0.025f, 100, 100);
	glPopMatrix(); // ��ũ �̵� ����

	glPopMatrix(); // ���� ���� ���� >> ����

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
