#include <gl/glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glBegin(GL_LINE_LOOP); // star
		glVertex3f(-0.75f, 0.9f, 0.0f); //a
		glVertex3f(-0.72f, 0.8f, 0.0f); //g
		glVertex3f(-0.62f, 0.8f, 0.0f); //f
		glVertex3f(-0.7f, 0.74f, 0.0f); //d
		glVertex3f(-0.66f, 0.64f, 0.0f); //j
		glVertex3f(-0.75f, 0.7f, 0.0f); //i
		glVertex3f(-0.84f, 0.64f, 0.0f); //h
		glVertex3f(-0.8f, 0.74f, 0.0f); //e
		glVertex3f(-0.88f, 0.8f, 0.0f); //c
		glVertex3f(-0.78f, 0.8f, 0.0f); //b
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP); // pentagon
	glVertex3f(0.0f, 0.9f, 0.0f); //a
	glVertex3f(0.15f, 0.8f, 0.0f); //f
	glVertex3f(0.1f, 0.6f, 0.0f); //j
	glVertex3f(-0.1f, 0.6f, 0.0f); //h
	glVertex3f(-0.15f, 0.8f, 0.0f); //c
	glEnd();
	glFlush();

	glBegin(GL_TRIANGLES); // triangle_white
	glVertex3f(0.75f, 0.92f, 0.0f); //a
	glVertex3f(0.92f, 0.629f, 0.0f); //f
	glVertex3f(0.58f, 0.629f, 0.0f); //f
	glEnd();
	glFlush();


	glBegin(GL_LINES); // ㄱ
	glVertex3f(-0.3f, 0.3f, 0.0f); 
	glVertex3f(0.0f, 0.3f, 0.0f); 
	glVertex3f(0.0f, 0.3f, 0.0f); 
	glVertex3f(-0.29f, -0.05f, 0.0f); 
	glEnd();
	glFlush();

	glBegin(GL_LINES); // ㅣ
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.1f, -0.05f, 0.0f); 
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP); //ㅁ
	glVertex3f(-0.2f, -0.07f, 0.0f); 
	glVertex3f(0.1f, -0.07f, 0.0f);
	glVertex3f(0.1f, -0.3f, 0.0f);
	glVertex3f(-0.2f, -0.3f, 0.0f);
	glEnd();
	glFlush();

	
	glBegin(GL_LINES); 
	glVertex3f(-0.84f, -0.6f, 0.0f); 
	glVertex3f(-0.09f, -0.6f, 0.0f); 
	glVertex3f(-0.84f, -0.8f, 0.0f); 
	glVertex3f(-0.09f, -0.8f, 0.0f); 
	glVertex3f(0.35f, -0.59f, 0.0f); 
	glVertex3f(0.84f, -0.59f, 0.0f); 
	glVertex3f(0.84f, -0.59f, 0.0f); 
	glVertex3f(0.84f, -0.79f, 0.0f); 
	glVertex3f(0.84f, -0.79f, 0.0f); 
	glVertex3f(0.35f, -0.79f, 0.0f); 

	glEnd();
	glFlush();


	glColor3f(1.0, 0.7, 0.0);
	glBegin(GL_TRIANGLES); // triangle_yellow
	glVertex3f(0.75f, 0.9f, 0.0f);
	glVertex3f(0.9f, 0.64f, 0.0f); 
	glVertex3f(0.6f, 0.64f, 0.0f);
	glEnd();
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Lecture");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
