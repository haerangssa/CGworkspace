#include <iostream>
#include <gl/glut.h>
using namespace std;
#define WIDTH 600
#define HEIGHT 600
float cutoff = 10;
float attenuation = 0;
float spin = 0;
int ltype = 1;
bool rotating = false;   
GLfloat position[] = { 0, 0, 1, 1 };

void drawLightPosition() {
    // 조명 위치를 빨간 큐브로 표시
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0, 0, 1);
    glScalef(0.1, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 30);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    if (rotating) {
        glRotatef(spin, 0, 1, 0);  // Y축 기준 회전
    }

    // LIGHT
    switch (ltype) {
    case 1: // Point Light
        position[3] = 1;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
        break;
    case 2: // Directional Light
        position[3] = 0;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        break;
    case 3: // Spotlight
        position[3] = 1;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        GLfloat sd[] = { 0.3, 0.0, -1.0 };
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sd);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff); 
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, attenuation);
        break;
    }
    drawLightPosition();
    glPopMatrix();

    glColor3f(1, 0, 1);
    glutSolidTorus(0.1, 0.3, 100, 100);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        position[2] += 0.2;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        break;
    case '-':
        position[2] -= 0.2;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        break;
    case '1':
        ltype = 1;
        break;
    case '2':
        ltype = 2;
        break;
    case '3':
        ltype = 3;
        break;
    case 's':
        rotating = !rotating;
        if (!rotating) {
            spin = 0;
        }
        break;
    case 'a':
        if (cutoff < 90) {
            cutoff += 5.0;
        }
        break;
    case 'b':
        if (cutoff > 0) {
            cutoff -= 5.0;
        } 
        break;
    case 'c':
        if (attenuation < 128) {
            attenuation += 4.0;
        }
        break;
       
    case 'd':
        if (attenuation > 0) {
            attenuation -= 4.0;
         }
        break;

    }
    glutPostRedisplay();
}

void idle() {
    if (rotating) {
        spin += 1.0;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Light Control");

    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}