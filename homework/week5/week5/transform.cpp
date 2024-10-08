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
	glRotatef(-45.0, 0.0, 0.0, 1.0); // 원래 축

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
	glTranslatef(0.6, 0.0, 0.0); // 이러면 축이 1사1ㅜㄴ면이 y로 바뀜
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
	glTranslatef(0.0, 0.6, 0.0); // 노랑 위치

	//inverse transformation2
	glTranslatef(0.0, 0.6, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0); // 빨강 위치

	// Translation & Rotation
	glRotatef(45.0, 0.0, 0.0, 1.0); // 여기 왜 마이너스 45가 아니지?
	glTranslatef(-0.6, 0.0, 0.0);
	// Pink Cube ***
	glColor3f(1.0, 0.0, 1.0);
	glutSolidCube(0.3);
	
	// Inverse Transformation
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0); // 원래 축

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