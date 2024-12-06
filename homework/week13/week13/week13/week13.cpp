#include <iostream>
#include <GL/glut.h>
using namespace std;

bool dir = true;
#define WIDTH 800
#define HEIGHT 800

GLfloat position[] = { 0.0, 15.0, 10.0, 1.0 }; // 조명 위치
float angle = 0.0; 

// 구 위치를 지정
void placeSphere(float x, float y, GLfloat* mat_a, GLfloat* mat_d, GLfloat* mat_s, GLfloat* low_sh, GLfloat* emission) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f); 

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

    glutSolidSphere(0.3, 100, 100);
    glPopMatrix();
}

// 조명 및 기본 설정
void setLighting() {
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, 1, 10); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    angle += 0.02; 
    if (angle >= 360.0) angle -= 360.0; 
    position[0] = 2.0f * cos(angle); 
    position[1] = 2.0f * sin(angle); 
    position[2] = 2.0f; 

    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); 
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    setLighting(); 

    //재질 및 색상 
    GLfloat mat_a1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_d1[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_s1[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat low_sh1[] = { 0.0 };
    GLfloat emission1[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat mat_a2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_d2[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_s2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_sh2[] = { 5.0 };
    GLfloat emission2[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat mat_a3[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_d3[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_s3[] = { 1.0,1.0,1.0,1.0 };
    GLfloat low_sh3[] = { 128 };
    GLfloat emission3[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat mat_a4[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_d4[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_s4[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat low_sh4[] = { 0 };
    GLfloat emission4[] = { 0.25, 0.1, 0, 1.0 };

    // 첫 번째 행
    placeSphere(-1.5f, 1.5f, mat_a1, mat_d1, mat_s1, low_sh1, emission1);
    placeSphere(-0.5f, 1.5f, mat_a2, mat_d2, mat_s2, low_sh2, emission2);
    placeSphere(0.5f, 1.5f, mat_a3, mat_d3, mat_s3, low_sh3, emission3);
    placeSphere(1.5f, 1.5f, mat_a4, mat_d4, mat_s4, low_sh4, emission4);

    // 두 번째 행
    GLfloat mat_d5[] = { 0.5, 0.7, 1.0, 1.0 };
    GLfloat emission5[] = { 0.3,0.2,0.2,1.0 };
    placeSphere(-1.5f, 0.5f, mat_a1, mat_d5, mat_s1, low_sh1, emission3);
    placeSphere(-0.5f, 0.5f, mat_a2, mat_d5, mat_s2, low_sh2, emission3);
    placeSphere(0.5f, 0.5f, mat_a3, mat_d5, mat_s3, low_sh3, emission3);
    placeSphere(1.5f, 0.5f, mat_a4, mat_d5, mat_s4, low_sh4, emission5);

    // 세 번째 행
    GLfloat mat_d6[] = { 0.6, 0.7, 0.5, 1.0 }; 
    GLfloat emission6[] = { 0.5, 0.4, 0.3, 1.0 };
    placeSphere(-1.5f, -0.5f, mat_a1, mat_d6, mat_s1, low_sh1, emission3);
    placeSphere(-0.5f, -0.5f, mat_a2, mat_d6, mat_s2, low_sh2, emission3);
    placeSphere(0.5f, -0.5f, mat_a3, mat_d6, mat_s3, low_sh3, emission3);
    placeSphere(1.5f, -0.5f, mat_a4, mat_d6, mat_s4, low_sh4, emission6);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Lighting Movement");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
