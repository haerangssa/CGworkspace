/*#include<gl/glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// Red Cube
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(0.3);

	// Translation & Rotation
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(0.6, 0.0, 0.0);
	// Green Cube
	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(0.3);

	// Inverse Transformation
	// Inverse Rotation, Inverse Translation
	glTranslatef(-0.6, 0.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0); // ���� ��

	// Rotation & Translation
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	// Blue Cube
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(0.3);

	// Inverse Transformation
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.6, 0.0, 0.0); 
	
	// Rotation & Translation
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glTranslatef(0.6, 0.0, 0.0); // �̷��� ���� 1��1�̤����� y�� �ٲ�
	// Yellow Cube
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCube(0.3);

	// Rotation & Translation
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	// SkyBlue Cube ***
	glColor3f(0.0, 1.0, 1.0);
	glutSolidCube(0.3);

	// Inverse Transformation1
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.6, 0.0); // ��� ��ġ

	//inverse transformation2
	glTranslatef(0.0, 0.6, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0); // ���� ��ġ

	// Translation & Rotation
	glRotatef(45.0, 0.0, 0.0, 1.0); // ���� �� ���̳ʽ� 45�� �ƴ���?
	glTranslatef(-0.6, 0.0, 0.0);
	// Pink Cube ***
	glColor3f(1.0, 0.0, 1.0);
	glutSolidCube(0.3);
	
	// Inverse Transformation
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0); // ���� ��

	// Rotation & Translation
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.6, 0.0);
	//Gray Cube
	glColor3f(0.5, 0.5, 0.5);
	glutSolidCube(0.3);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

*/