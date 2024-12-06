#include <GL/glut.h>
#include <iostream>
#include <string>
using namespace std;

#define PI 3.141592
float flowerScale = 1.0f; 
// 회전 관련
float rotationAngleX = 0.0f, rotationAngleY = 0.0f;
float characterRotation = 0.0f;
float kimRotation = 0.0f;

float jump = 0.0f;         // 캐릭터의 수직 위치
float jumpSpeed = 0.002f;    // 위아래 이동 속도
bool isJumpingUp = true;
bool jumpEnabled = true;
// 캐릭터 애니메이션 관련
float arm = 0.0f;
float armSpeed = 0.1f;
float stem = 1.0f;
float leg = 1.0f;
float flower = 0.0f;
float head = 0.0f;
int legDirection = 1;



// 변환 관련 
struct Transform {
    float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
    float translateX = 0.0f, translateY = 0.0f, translateZ = 0.0f;
    float rotateXKim = 0.0f, rotateYKim = 0.0f, rotateZKim = 0.0f;
    float rotateXTeapot = 0.0f, rotateYTeapot = 0.0f, rotateZTeapot = 0.0f;
    float tanslateC = 0.0f;
    float boxRotation1 = 0.0f;
    float boxRotation2 = 0.0f;
    float boxRotation3 = 0.0f;
    float boxRotation4 = 0.0f;
    float boxRotation5 = 0.0f;
    float boxRotation6 = 0.0f;
    float boxRotation7 = 0.0f;
    float box1X = 0.0f;  // 첫 번째 박스 부분 이동
    float box1Y = 0.0f;
    float kimWholeX = 0.0f;  // 김 전체 이동
    float kimWholeY = 0.0f;
    bool isPouring = false;  // 물 붓기 애니메이션 진행 중인지
    int pourCount = 0;      // 물 붓기 반복 횟수
    float pourAngle = 0.0f; // 현재 물 붓기 각도
    bool increasing = true;  // 각도가 증가하는 중인지
    float kimGrowth = 1.0f;
};

float rotationAngle = 0.0f;
// 공전 관련
float teapotOrbitAngle = 0.0f;
float coneOrbitAngle = 0.0f;
Transform transform;

void drawBox() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
}

void drawKim() {
    glTranslatef(transform.kimWholeX, transform.kimWholeY, 0.0);

    glTranslatef(transform.translateX, transform.translateY, transform.translateZ);
    glScalef(transform.scaleX, transform.scaleY, transform.scaleZ);
    glRotatef(kimRotation, 0.0, 1.0, 0.0);

    glScalef(transform.kimGrowth, transform.kimGrowth, transform.kimGrowth);
    
    for(int i = 0; i < 7; i++) {
        glPushMatrix();
        
        switch (i) {
        case 0: glRotatef(transform.boxRotation1, 1.0, 1.0, 1.0); 
            glTranslatef(transform.box1X, transform.box1Y, 0.0); 
            break;
        case 1: glRotatef(transform.boxRotation2, 1.0, 1.0, 1.0); break;
        case 2: glRotatef(transform.boxRotation3, 1.0, 1.0, 1.0); break;
        case 3: glRotatef(transform.boxRotation4, 1.0, 1.0, 1.0); break;
        case 4: glRotatef(transform.boxRotation5, 1.0, 1.0, 1.0); break;
        case 5: glRotatef(transform.boxRotation6, 1.0, 1.0, 1.0); break;
        case 6: glRotatef(transform.boxRotation7, 1.0, 1.0, 1.0); break;
        }


        glRotatef(transform.rotateXKim, 1.0, 0.0, 0.0);
        glRotatef(transform.rotateYKim, 0.0, 1.0, 0.0);
        glRotatef(transform.rotateZKim, 0.0, 0.0, 1.0);

        switch(i) {
            case 0: // 박스1 (김 구성요소들)
                glRotatef(55.0, 1.0, 0.0, 1.0);
                glTranslatef(-0.1f, 0.3f, 0.0f);
                glRotatef(45.0, 0.0, 0.0, 1.0);
                glScalef(0.03, 0.15, 0.05);
                break;
            case 1: // 2
                glRotatef(-15.0, 0.0, 1.0, 1.0);
                glRotatef(70.0, 0.0, 1.0, 0.0);
                glTranslatef(-0.35f, -0.025f, 0.0f);
                glRotatef(45.0, 1.0, 1.0, 1.0);
                glScalef(0.05, 0.2, 0.03);
                break;
            case 2: // 3
                glRotatef(-15.0, 0.0, 0.0, 1.0);
                glTranslatef(-0.2f, -0.4f, 0.0f);
                glRotatef(45.0, 1.0, 1.0, 1.0);
                glScalef(0.05, 0.1, 0.05);
                break;
            case 3: // 4
                glTranslatef(-0.15f, -0.25f, 0.0f);
                glRotatef(45.0, 1.0, 1.0, 0.0);
                glRotatef(-90.0, 0.0, 0.0, 1.0);
                glScalef(0.03, 0.2, 0.03);
                break;
            case 4: // 5
                glRotatef(5.0, 0.0, 0.0, 1.0);
                glTranslatef(0.025f, 0.0f, 0.0f);
                glRotatef(45.0, 1.0, 1.0, 0.0);
                glScalef(0.03, 0.2, 0.03);
                break;
            case 5: // 6
                glRotatef(-25.0, 0.0, 0.0, 1.0);
                glTranslatef(0.15f, -0.25f, 0.0f);
                glRotatef(45.0, 1.0, 1.0, 1.0);
                glScalef(0.05, 0.1, 0.05);
                break;
            case 6: // 7 
                glTranslatef(-0.15f, -0.4f, 0.0f);
                glRotatef(45.0, 1.0, 1.0, 0.0);
                glRotatef(-90.0, 0.0, 0.0, 1.0);
                glScalef(0.03, 0.2, 0.03);
                break;
        }
        drawBox();
        glPopMatrix();
    }
}

void drawCharacter() {

    float currentX = transform.translateX;
    float currentY = transform.translateY;
    float currentZ = transform.translateZ;

    glTranslatef(currentX + transform.scaleX / 2, currentY + transform.scaleY / 2, currentZ);
    glScalef(transform.scaleX, transform.scaleY, transform.scaleZ);
    glTranslatef(-(currentX + transform.scaleX / 2), -(currentY + transform.scaleY / 2), -currentZ);

    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(characterRotation, 0.0, 1.0, 0.0);

    // 몸통
    glTranslatef(0.5, 0.4, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.05, 0.0);
    glScalef(0.25, 0.4, 0.1);
    glColor3f(0.5, 0.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // 오른팔
    glPushMatrix();
    glTranslatef(0.2, 0.2, 0.0);
    glRotatef(arm, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.1, 0.05, 0.05);
    drawBox();
    glPopMatrix();

    // 줄기
    glPushMatrix();
    glScalef(flowerScale, flowerScale, flowerScale);
    glTranslatef(0.1, 0.0, 0.0);
    glRotatef(stem, 0.0, 1.0, 0.0);
    glScalef(0.03, 0.2, 0.03);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // 꽃 가운데..
    glPushMatrix();
    glScalef(flowerScale, flowerScale, flowerScale);
    glTranslatef(0.1, 0.1, 0.0);
    glColor3f(1.0, 0.5, 0.5);
    glutSolidTorus(0.03, 0.0, 20, 20);
    glPopMatrix();

    // 꽃잎
    glPushMatrix();
    glScalef(flowerScale, flowerScale, flowerScale);
    glTranslatef(0.1, 0.15, 0.0);
    for(int i = 0; i < 5; i++) {
        glPushMatrix();
        glScalef(0.035, 0.035, 0);
        glColor3f(1.0, 0.3, 0.0);
        glutSolidCube(1.0);
        glPopMatrix();
        
        if(i < 4) {
            glRotatef(i == 0 ? 60.0 : (i == 1 ? 70.0 : (i == 2 ? 90.0 : 70.0)), 0.0, 0.0, 1.0);
            glTranslatef(-0.05, i == 2 ? 0.043 : (i == 3 ? 0.03 : 0.025), 0.0);
        }
    }
    glPopMatrix();
    glPopMatrix();

    // 왼팔
    glPushMatrix();
    glTranslatef(-0.125, 0.2, 0.0);
    glRotatef(arm, 0.0, 0.0, 1.0);
    glTranslatef(-0.1, 0.0, 0.0);
    glScalef(0.2, 0.1, 0.1);
    glColor3f(0.8, 0.5, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // 머리
    glPushMatrix();
    glTranslatef(0.0, 0.35, 0.0);
    glRotatef(head, 0.0, 1.0, 0.0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 0.0, 1.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // 다리
    for(int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(i == 0 ? -0.05f : 0.05f, -0.14, 0.0);
        glRotatef(i == 0 ? leg : -leg, 0.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 0.8, 1.0);
        glVertex3f(-0.04, 0.0, 0.0);
        glVertex3f(0.04, 0.0, 0.0);
        glVertex3f(0.0, -0.25, 0.0);
        glEnd();
        glPopMatrix();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glLoadIdentity();
    glPushMatrix();
    // 김모형
    drawKim();

    // 티팟
    glPushMatrix();
    glRotatef(teapotOrbitAngle, 0.0, 1.0, 0.0);
    glTranslatef(-0.5, 0.5, 0.0);
    glRotatef(transform.pourAngle, 0.0, 0.0, 1.0);
    glRotatef(transform.rotateYTeapot, 0.0, 1.0, 0.0);
    glRotatef(transform.rotateXTeapot, 1.0, 0.0, 0.0);
    glRotatef(transform.rotateZTeapot, 0.0, 0.0, 1.0);
    glRotatef(-35.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glScalef(0.5, 0.5, 1.0);
    glutSolidTeapot(0.3);
    glColor3f(1, 0, 0);
    glutWireTeapot(0.3);
    glPopMatrix();

    // 원뿔
    glPushMatrix();
    glRotatef(coneOrbitAngle, 0.0, 1.0, 0.0);
    glTranslatef(-0.2, 0.3, 0.0);
    glRotatef(-45.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.1, 1.0);
    glutSolidCone(0.03, 0.1, 30, 30);
    glPopMatrix();
    glTranslatef(0.0f, jump, 0.0f);
    drawCharacter();
    glPopMatrix();
    glPopMatrix();
    glFlush();
}

void updateAnimation() {
    // 팔 
    arm += armSpeed;
    if (arm > 30.0f || arm < -30.0f) {
        armSpeed = -armSpeed;
    }

    // 다리 (키보드 입력 들어오면 멈추도록)
    if (jumpEnabled) { 
        leg += legDirection * 0.5f;
        if (leg > 45.0f || leg < -45.0f) {
            legDirection = -legDirection; 
            isJumpingUp = false;
        }
    }

    // 점프 모션 (키보드 입력 들어오면 멈추도록)
    if (jumpEnabled) {
        if (isJumpingUp) {
            jump += jumpSpeed;
            if (jump >= 0.05f) {
                isJumpingUp = false;
            }
        }
        else {
            jump -= jumpSpeed;
            if (jump <= -0.00f) {
                isJumpingUp = true;
            }
        }
    }

    // 물 붓기 ( P 키 통해 작동 )
    if (transform.isPouring) {
        const float POUR_SPEED = 0.5f;

        if (transform.increasing) {
            transform.pourAngle -= POUR_SPEED;  
            if (transform.pourAngle <= -25.0f) {
                transform.increasing = false;
            }
        }
        else {
            transform.pourAngle += POUR_SPEED;  
            if (transform.pourAngle >= 0.0f) {
                transform.increasing = true;
                transform.pourCount++;

                //2번 반복
                if (transform.pourCount >= 4) {  
                    transform.isPouring = false;
                    transform.pourCount = 0;
                    //김 크기 증가
                    transform.kimGrowth = 1.2f;  
                }
            }
        }

        coneOrbitAngle = transform.pourAngle * 0.5f; 
    }

    glutPostRedisplay(); // 애니 반복
}

void keyboard(unsigned char key, int x, int y) {
    jumpEnabled = false;
    switch (key) {
    case 'o': // 공전과 자전 동시에 실행
        kimRotation += 2.0f;  // 김 모형 자전
        characterRotation += 2.0f;  // 캐릭터 자전
        teapotOrbitAngle -= 3.0f;  // 티팟 공전
        coneOrbitAngle += 5.0f;  // 콘 공전
        break;
    case 'u': // 반시계 방향 
        kimRotation -= 2.0f;
        characterRotation -= 2.0f;
        teapotOrbitAngle += 3.0f;
        coneOrbitAngle -= 5.0f;
        break;
    case '1': transform.boxRotation1 += 5.0f; break; // 각각의 박스 rotation
    case '2': transform.boxRotation2 += 5.0f; break;
    case '3': transform.boxRotation3 += 5.0f; break;
    case '4': transform.boxRotation4 += 5.0f; break;
    case '5': transform.boxRotation5 += 5.0f; break;
    case '6': transform.boxRotation6 += 5.0f; break;
    case '7': transform.boxRotation7 += 5.0f; break;

    case 'X': rotationAngleX += 5.0; break; //character
    case 'Y': rotationAngleY += 5.0; break;

    case 'w': transform.translateY += 0.05f;
        leg += 5.0 * legDirection;
        if (leg >= 30 || leg <= -30) legDirection = -legDirection;break;
    case 's': transform.translateY -= 0.05f;
        leg += 5.0 * legDirection;
        if (leg >= 30 || leg <= -30) legDirection = -legDirection;
        break;
    case 'a': transform.translateX -= 0.05f;
        leg += 5.0 * legDirection;
        if (leg >= 30 || leg <= -30) legDirection = -legDirection;
        break;
    case 'd': transform.translateX += 0.05f;
        leg += 5.0 * legDirection;
        if (leg >= 30 || leg <= -30) legDirection = -legDirection;
        break;
    case 'q': transform.scaleX += 0.05f; break;
    case 'e': transform.scaleX -= 0.05f; break;
    case 'r': transform.scaleY += 0.05f; 
        flowerScale += 0.1f;
        if (flowerScale > 2.0f) flowerScale = 2.0f;
        break;
    case 'f': transform.scaleY -= 0.05f; break;
    case 'x': transform.rotateXKim += 10.0f; 
        flowerScale += 0.1f;
        if (flowerScale > 2.0f) flowerScale = 2.0f; break;
    case 'y': transform.rotateYKim += 10.0f; 
        flowerScale += 0.1f;
        if (flowerScale > 2.0f) flowerScale = 2.0f; break;
    case 'z': transform.rotateZKim += 10.0f; 
        flowerScale += 0.1f;
        if (flowerScale > 2.0f) flowerScale = 2.0f; break;
    case 'p': transform.rotateXTeapot += 10.0f; break;
    case 'l': transform.rotateYTeapot += 10.0f; break;
    case 'm': transform.rotateZTeapot += 10.0f; break;
        // 박스1 부분 이동 
    case 't': transform.box1Y += 0.01f; break;  // 박스를 위로
    case 'g': transform.box1Y -= 0.01f; break;  // 박스를 아래로
    case 'j': transform.box1X -= 0.01f; break;  // 박스를 왼쪽으로
    case 'h': transform.box1X += 0.01f; break;  // 박스를 오른쪽으로
        // 김 전체 이동 (대문자 T,F,G,H 키 사용)
    case 'T': transform.kimWholeY += 0.05f; 
         transform.box1Y -= 0.01f; break;  // 전체를 위로
    case 'G': transform.kimWholeY -= 0.05f;
        transform.box1Y += 0.01f; break;  // 전체를 아래로
    case 'J': transform.kimWholeX -= 0.05f;
         transform.box1X += 0.01f; break;  // 전체를 왼쪽으로
    case 'H': transform.kimWholeX += 0.05f;
        transform.box1X -= 0.01f; break;// 전체를 오른쪽으로
    case 'P':  // 'p' 키로 물 붓기 애니메이션 시작
        if (!transform.isPouring) {
            transform.isPouring = true;
            transform.pourCount = 0;
            transform.pourAngle = 0.0f;
            transform.increasing = true;
        }
    case '+': flowerScale += 0.1f;
        if (flowerScale > 2.0f) flowerScale = 2.0f;
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Model Transformation");

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(updateAnimation);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
