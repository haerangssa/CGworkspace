#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;
float moveStep = 2.0f;
bool dir = true;
GLuint texID1, texID2;

bool isCameraAnimating = false;
int animationStep = 0;
bool isReturningToOrigin = false; 
bool isFishFollowMode = false;
int currentFishFollowed = 0;
float originalCameraX, originalCameraY, originalCameraZ;
float originalCenterX, originalCenterY, originalCenterZ;
float originalUpX, originalUpY, originalUpZ;

bool lightRotating = false; 
bool randomColorChange = false;  
float rotationAngle = 0.0f;
float rotationSpeed = 5.0f; 

GLfloat spotlightPos[] = { -10.0f, 15.0f, -10.0f, 1.0f }; 
GLfloat spotlightDir[] = { 0.5f, -1.0f, 0.5f };  
GLfloat ambient1[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat diffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular1[] = { 0.5f, 1.0f, 0.2f, 1.0f };
float spotlightCutoff = 30.0f; 
float spotlightExponent = 10.0f; 
bool spotlightMoving = false;
int spotlightDirectionToggle = -1;

GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat mat_a[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_d[] = { 0.1, 0.5, 1.0, 1.0 };
GLfloat mat_s[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat low_sh[] = { 100 };
GLfloat emission[] = { 0, 0, 0, 1.0 };

GLfloat mat_a0[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat mat_d0[] = { 0.1, 0.5, 1.0, 1.0 };
GLfloat mat_s0[] = { 0.5, 0, 0, 1.0 };
GLfloat low_sh0[] = { 100.0 };
GLfloat emission0[] = { 0, 0, 0, 1.0 };

GLfloat mat_a1[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_d1[] = { 0.0, 0.5, 1.0, 1.0 };
GLfloat mat_s1[] = { 0.0, 0.5, 0.0, 1.0 };
GLfloat low_sh1[] = { 100.0 };
GLfloat emission1[] = { 0.5, 0.5, 0.0, 1.0 };

GLfloat mat_a2[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_d2[] = { 0.8, 0.6, 0.0, 1.0 };
GLfloat mat_s2[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat low_sh2[] = { 100.0 };
GLfloat emission2[] = { 0.0, 0.0, 0.0, 1.0 };
float cameraX = 0.0f, cameraY = 10.0f, cameraZ = 40.0f; 
float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;   
float upX = 0.0f, upY = 1.0f, upZ = 0.0f; 
float moveSpeed = 4.0f; 
float stepX = 0.5f; 
float stepY = 0.2f; 

float lightX = 0.0f, lightY = 1.0f, lightZ = 2.0f;

float colorChangeSpeed = 0.1f;

int lightMode = 1;             
float lightPosX = 0.0f;          
float lightPosY = 15.0f;
float lightPosZ = 10.0f;

float lightChangeSpeed = 0.01f;
int animationCounter = 0; 

float mirrorBallRotationAngle = 0.0f;
void setSpotlight() {
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, spotlightPos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotlightCutoff);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotlightExponent);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
}

void spotLightPosition() {
    if (spotlightMoving) {
        spotlightPos[0] = (spotlightDirectionToggle == -1) ? -10.0f : 10.0f;
        spotlightDirectionToggle *= -1;
        glutPostRedisplay();
    }
}

void generateRandomColor(GLfloat* color) {
    color[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
    color[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
    color[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); 
}
void placeTorus(GLfloat* mat_a, GLfloat* mat_d, GLfloat* mat_s, GLfloat* low_sh, GLfloat* emission) {
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glPushMatrix();
    glTranslatef(-15, -8, 0);
    glColor3f(1, 0, 1);
    glRotatef(mirrorBallRotationAngle, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(1, 3, 100, 100);
    glPopMatrix();
}

void placeSphere(GLfloat* mat_a, GLfloat* mat_d, GLfloat* mat_s, GLfloat* low_sh, GLfloat* emission) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

    glPushMatrix();
    glTranslatef(-15, -8, 0);
    glRotatef(mirrorBallRotationAngle, 1.0f, 0.0f, 0.0f);
    glutWireSphere(2, 100, 100);
    glPopMatrix();
}
GLfloat position[] = { 0.5, 5, 30, 0 };
void setLighting() {
    GLfloat lightPosition[] = { lightPosX, lightPosY, lightPosZ, position[3]};
    if (randomColorChange) {
        generateRandomColor(ambient);
        generateRandomColor(diffuse);
        generateRandomColor(specular);
    }
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}
void updateLightRotation() {
    if (lightRotating) {
        rotationAngle += rotationSpeed;
        if (rotationAngle >= 170.0f) {
            rotationAngle -= 170.0f; 
        }
        float radius = 5.0f;
        lightPosX = radius * cos(rotationAngle * 3.14f / 90.0f);
        lightPosZ = radius * sin(rotationAngle * 3.14f / 90.0f);
    }
}
bool isMirrorBallRotating = false;
void drawMirrorBall(GLfloat* mat_a, GLfloat* mat_d, GLfloat* mat_s, GLfloat* low_sh, GLfloat* emission) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

    glPushMatrix();
    glTranslatef(0.0f, 10.0f, -5.0f);
    glRotatef(mirrorBallRotationAngle, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, texID1);
    gluSphere(quad, 3.0, 50, 50);
    gluDeleteQuadric(quad);
    glDisable (GL_TEXTURE_2D);

    glPopMatrix();
}
void drawKim(GLfloat* mat_a, GLfloat* mat_d, GLfloat* mat_s, GLfloat* low_sh, GLfloat* emission) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

    glPushMatrix();
    glTranslatef(0, 0, 0);
    
    // 첫 번째 획 (ㄱ)
    glPushMatrix();
    glTranslatef(-2, 2, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 4, 1);
    glutSolidCube(2);
    glPopMatrix();

    // 두 번째 획 (ㄱ)
    glPushMatrix();
    glTranslatef(2, -1, 0);
    glScalef(1, 4, 1);
    glutSolidCube(2);
    glPopMatrix();

    // ㅣ
    glPushMatrix();
    glTranslatef(6, -1, 0);
    glScalef(1, 6, 1);
    glutSolidCube(2);
    glPopMatrix();

    // 첫 번째 획 (ㅁ)
    glPushMatrix();
    glTranslatef(-4, -10, 0);
    glScalef(1, 3, 1);
    glutSolidCube(2);
    glPopMatrix();

    // 두 번째 획 (ㅁ)
    glPushMatrix();
    glTranslatef(1, -8, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 4, 1);
    glutSolidCube(2);
    glPopMatrix();

    // 세 번째 획 (ㅁ)
    glPushMatrix();
    glTranslatef(6, -10, 0);
    glScalef(1, 3, 1);
    glutSolidCube(2);
    glPopMatrix();

    // 네 번째 획 (ㅁ)
    glPushMatrix();
    glTranslatef(1, -12, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1, 4, 1);
    glutSolidCube(2);
    glPopMatrix();
}

const int numFish = 5; 
float fishPositions[numFish][3]; 
float fishDirections[numFish][3]; 
float fishSpeed = 0.5f;            

void initFish() {
    for (int i = 0; i < numFish; i++) {
        fishPositions[i][0] = (rand() % 21 - 10); 
        fishPositions[i][1] = (rand() % 16 - 7);   
        fishDirections[i][0] = (rand() % 2 == 0 ? 1 : -1) * 0.1f;
        fishDirections[i][1] = (rand() % 2 == 0 ? 1 : -1) * 0.1f;
    }
}

void drawFish(float x, float y, float z, GLfloat* mat_a, GLfloat* mat_d, GLfloat* mat_s, GLfloat* low_sh, GLfloat* emission) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.5f, 0.3f, 0.2f);
    glutSolidSphere(2.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y, z - 2.0f);
    glScalef(0.2f, 0.2f, 0.5f);
    glutSolidCone(1.5, 3.0, 20, 10);
    glPopMatrix();
}

void updateFish() {
    for (int i = 0; i < numFish; i++) {
        fishPositions[i][0] += fishDirections[i][0] * fishSpeed;
        fishPositions[i][1] += fishDirections[i][1] * fishSpeed;
        if (fishPositions[i][0] > 10.0f || fishPositions[i][0] < -10.0f) fishDirections[i][0] *= -1;
        if (fishPositions[i][1] > 7.5f || fishPositions[i][1] < -7.5f) fishDirections[i][1] *= -1;

    }
}

void drawAquarium() {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, -5.0f);
    glScalef(3.0f, 1.5f, 1.0f);
    glutWireCube(20.0);
    glPopMatrix();

    // 하늘색 (수족관 천장)
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 1.0f);
    glTranslatef(0.0f, 14.0f, -3.0f);
    glRotatef(90, 1, 0, 0);
    glScalef(3.0f, 0.8f, 0.1f);
    glutSolidCube(20.0);
    glPopMatrix();

    // 어두운 회색 (수족관 바닥)
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, -14.0f, -3.0f);
    glRotatef(90, 1, 0, 0);
    glScalef(3.0f, 0.8f, 0.1f);
    glutSolidCube(20.0);
    glPopMatrix();

    // 하늘색 벽 (수족관 뒤쪽)
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 1.0f);
    glTranslatef(0.0f, 0.0f, -15.0f);
    glScalef(3.0f, 1.5f, 0.1f);
    glutSolidCube(20.0);
    glPopMatrix();

    // 하늘색 벽 (수족관 왼쪽)
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 1.0f);
    glTranslatef(-29.0f, 0.0f, -5.0f);
    glScalef(0.1f, 1.5f, 1.0f);
    glutSolidCube(20.0);
    glPopMatrix();

    // 하늘색 벽 (수족관 오른쪽)
    glPushMatrix();
    glColor3f(0.2f, 0.7f, 1.0f);
    glTranslatef(29.0f, 0.0f, -5.0f);
    glScalef(0.1f, 1.5f, 1.0f);
    glutSolidCube(20.0);
    glPopMatrix();

    // 물고기 그리기
    for (int i = 0; i < numFish; i++) {
        drawFish(fishPositions[i][0], fishPositions[i][1], fishPositions[i][2],  mat_a,  mat_d, mat_s, low_sh, emission);
    }
}
void drawRoom() {
    // 바닥
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f); // 갈색
    glTranslatef(0.0f, -20.0f, 0.0f);
    glScalef(20.0f, 0.1f, 40.0f);  // 크기 축소
    glutSolidCube(10.0);
    glPopMatrix();

    // 천장
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.5f); // 밝은 회색
    glTranslatef(0.0f, 35.0f, 0.0f);
    glScalef(20.0f, 0.1f, 40.0f); // 크기 축소
    glutSolidCube(10.0);
    glPopMatrix();

    // 왼쪽 벽
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.9f); // 회색
    glTranslatef(-100.0f, 5.0f, 0.0f); // 위치 조정
    glScalef(0.1f, 6.0f, 40.0f);  // 크기 축소
    glutSolidCube(10.0);
    glPopMatrix();

    // 오른쪽 벽
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.9f); // 회색
    glTranslatef(100.0f, 5.0f, 0.0f);
    glScalef(0.1f, 6.0f, 40.0f);  // 크기 축소
    glutSolidCube(10.0);
    glPopMatrix();

    // 앞쪽 벽
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.7f); // 어두운 회색
    glTranslatef(0.0f, 5.0f, 100.0f); // 위치 조정
    glScalef(20.0f, 6.0f, 0.1f); // 크기 축소
    glutSolidCube(10.0);
    glPopMatrix();

    // 뒤쪽 벽
    glPushMatrix();
    glColor3f(0.5f, 0.7f, 0.5f); // 어두운 회색
    glTranslatef(0.0f, 5.0f, -100.0f); // 위치 조정
    glScalef(20.0f, 6.0f, 0.1f); // 크기 축소
    glutSolidCube(10.0);
    glPopMatrix();
}
int repeatCount = 0;
static float upAngle = 0.0f;
static int upStep = 0; 
static int transitionCount = 0;
static float transitionSpeed = 0.1f; 
void animateCamera() {
    if (!isCameraAnimating) return;

    switch (animationStep) {
    case 0: 
        cameraX += moveStep;
        if (cameraX >= 30.0f) animationStep++; 
        break;

    case 1:
        cameraZ -= moveStep;
        if (cameraZ <= -10.0f) animationStep++;
        break;

    case 2:
        cameraX -= moveStep;
        if (cameraX <= -30.0f) animationStep++;
        break;

    case 3:
        cameraZ += moveStep;
        if (cameraZ >= 30.0f) animationStep++;
        break;

    case 4:
        cameraX += moveStep;
        if (cameraX >= 0.0f) animationStep++; 
        break;
    case 5: 
        if (repeatCount < 3) { 
            if (repeatCount % 2 == 0) { 
                cameraX -= (cameraX - 0.0f) * 0.1f;
                cameraZ -= (cameraZ - 0.0f) * 0.1f;
                if (fabs(cameraX) < 0.5f && fabs(cameraZ) < 0.5f) repeatCount++;
            }
            else { 
                cameraX += (0.0f - cameraX) * 0.1f;
                cameraZ += (40.0f - cameraZ) * 0.1f;
                if (fabs(cameraX - 0.0f) < 0.5f && fabs(cameraZ - 40.0f) < 0.5f) repeatCount++;
            }
        }
        else { 
            repeatCount = 0;
            animationStep=0;
        }
        break; 
        }
        centerX = 0.0f;
        centerY = 0.0f;

        glutPostRedisplay();
    }
    
void FishFollow() {
    isFishFollowMode = !isFishFollowMode;
    if (isFishFollowMode) {
        originalCameraX = cameraX;
        originalCameraY = cameraY;
        originalCameraZ = cameraZ;
        originalCenterX = centerX;
        originalCenterY = centerY;
        originalCenterZ = centerZ;
        originalUpX = upX;
        originalUpY = upY;
        originalUpZ = upZ;

        currentFishFollowed = rand() % numFish;
    }
    else {
        cameraX = originalCameraX;
        cameraY = originalCameraY;
        cameraZ = originalCameraZ;
        centerX = originalCenterX;
        centerY = originalCenterY;
        centerZ = originalCenterZ;
        upX = originalUpX;
        upY = originalUpY;
        upZ = originalUpZ;
    }
}
void updateFishFollowCamera() {
    if (!isFishFollowMode) return;
    cameraX = fishPositions[currentFishFollowed][0];
    cameraY = fishPositions[currentFishFollowed][1] + 2.0f; 
    cameraZ = fishPositions[currentFishFollowed][2] + 5.0f; 

    centerX = fishPositions[currentFishFollowed][0] + fishDirections[currentFishFollowed][0] * 10;
    centerY = fishPositions[currentFishFollowed][1];
    centerZ = fishPositions[currentFishFollowed][2];

    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
}

void display() {
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ, centerX, centerY, centerZ, upX, upY, upZ);
    switch (lightMode) {
    case 1: 
        position[3] = 1;
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        break;
    case 2: 
        position[3] = 0;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        break;
    case 3: 
        position[3] = 1;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        GLfloat sd[] = { 0.3, -10, -30.0 };
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sd);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 128);
        break;
    }
    setLighting();
    updateLightRotation(); 
    setSpotlight();   
    spotLightPosition();

    glDisable(GL_LIGHTING);
    drawRoom();
    drawAquarium();
    glEnable(GL_LIGHTING);

    drawMirrorBall(mat_a0, mat_d0, mat_s0, low_sh0, emission0);
    drawKim(mat_a, mat_d, mat_s, low_sh, emission); 
    placeSphere(mat_a1, mat_d1, mat_s1, low_sh1, emission1);
    placeTorus(mat_a2, mat_d2, mat_s2, low_sh2, emission2);

    glutSwapBuffers();
}
void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    srand(static_cast<unsigned int>(time(0))); 
    glClearColor(0.0, 0.0, 0.0, 1.0);        
    isCameraAnimating = false;
}
void timer(int value) {
    if (isCameraAnimating) {
        animateCamera();
    }
    updateFish(); 
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void updateLighting(int value) {
    glutPostRedisplay();
    glutTimerFunc(50, updateLighting, 0);
}

void spotlightProperty(unsigned char key) {
    switch (key) {
    case 'P': spotlightCutoff += 1.0f; break; 
    case 'p': spotlightCutoff -= 1.0f; break; 
    case '8': spotlightExponent += 1.0f; break; 
    case '9': spotlightExponent -= 1.0f; break; 
    case 'R': ambient1[0] += 0.1f; break; 
    case 'r': ambient1[0] -= 0.1f; break; 
    case 'G': diffuse1[1] += 0.1f; break;
    case 'g': diffuse1[1] -= 0.1f; break;
    case 'Y': specular1[1] += 0.05f; break;
    case 'y': specular1[1] -= 0.05f; break;
    case 'T': spotlightMoving = !spotlightMoving;break;
    }
    if (spotlightCutoff > 90.0f) spotlightCutoff = 90.0f;
    if (spotlightCutoff < 0.0f) spotlightCutoff = 0.0f;
    if (spotlightExponent > 128.0f) spotlightExponent = 128.0f;
    if (spotlightExponent < 0.0f) spotlightExponent = 0.0f;
    for (int i = 0; i < 3; i++) {
        if (ambient1[i] < 0.0f) ambient1[i] = 0.0f;
        if (ambient1[i] > 1.0f) ambient1[i] = 1.0f;
        if (diffuse1[i] < 0.0f) diffuse1[i] = 0.0f;
        if (diffuse1[i] > 1.0f) diffuse1[i] = 1.0f;
        if (specular1[i] < 0.0f) specular1[i] = 0.0f;
        if (specular1[i] > 1.0f) specular1[i] = 1.0f;
    }
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    // 카메라 position
    case 'w': cameraZ -= moveSpeed; break;
    case 's': cameraZ += moveSpeed; break;
    case 'a': cameraX -= moveSpeed; break;
    case 'd': cameraX += moveSpeed; break;
    case 'q': cameraY += moveSpeed; break;
    case 'e': cameraY -= moveSpeed; break;
    // lookat
    case 'i': centerY += moveSpeed; break;
    case 'k': centerY -= moveSpeed; break;
    case 'j': centerX -= moveSpeed; break;
    case 'l': centerX += moveSpeed; break;
    case 'u': centerZ -= moveSpeed; break;
    case 'o': centerZ += moveSpeed; break;
    // upvector
    case 'z': upX -= 0.5f; break; // X축 방향으로 기울임
    case 'x': upX += 0.5f; break;
    case 'c': upY -= 45.0f; break; // Y축 방향으로 기울임
    case 'v': upY += 45.0f; break;

    case '1': lightMode = 1; break; // 일반 실내광
    case '2': lightMode = 2; break; // 태양광
    case '3': lightMode = 3; break; // 스포트라이트

    case 'A':
        lightRotating = !lightRotating;
        randomColorChange = !randomColorChange;
        isMirrorBallRotating = !isMirrorBallRotating;
        break;
    case 'D': lightPosX += 5.0f; break;
    case 'Q': lightPosX -= 5.0f; break;
    case 'W': lightPosY += 5.0f; break;
    case 'S': lightPosY -= 5.0f; break;
    case 'M': mat_a0[0] += 0.5; mat_d0[0] += 0.5;
        mat_a0[1] += 0.5; mat_s0[1] += 0.5;
        mat_a0[2] += 0.5; low_sh0[0] += 3;
        emission0[1] += 0.2;
        break;
    case 'm': mat_a0[0] -= 0.5; mat_d0[1] -= 0.5;
        mat_a0[1] -= 0.5; mat_s0[0] -= 0.1;
        mat_a0[2] -= 0.5; low_sh0[0] -= 0.3;
        emission0[0] -= 0.2;
        break;
    case 'C':
        if (isCameraAnimating) {
           cameraX = 0;
           cameraY = 10;
           cameraZ = 40;
           centerX = 0;
           centerY = 0;
           centerZ = 0;
           upX = 0.0f;
           upY = 1.0f;
           upZ = 0.0f;
           isCameraAnimating = false;
        } else {
            isCameraAnimating = true; 
            animationStep = 0; 
        }
        break;
    case 'F':
        FishFollow();
        break;
    default: spotlightProperty(key); break;
    }
    glutPostRedisplay();
}
void idle(){
    if (isFishFollowMode) {
        updateFishFollowCamera();
    }
    if (isMirrorBallRotating) {
        mirrorBallRotationAngle += 1.5f; 
        if (mirrorBallRotationAngle >= 360.0f) {
            mirrorBallRotationAngle -= 360.0f;
        }
    }
    spotLightPosition();
    glutPostRedisplay();
}
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.552,0.552,-0.414,0.414,1.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
}
unsigned char header[54];
unsigned int dataPos;
unsigned int width, height;
unsigned int imageSize;
unsigned char* loadBMP(char* fname)
{
    FILE* file = fopen(fname, "rb"); 
    if (!file) {
        cout << "Image file could not be opened "
            << endl; return NULL;
    }
    if (fread(header, 1, 54, file) != 54) {
        cout << "Not a correct BMP file\n";
        return NULL;
    }
    if (header[0] != 'B' || header[1] != 'M') { 
        cout << "Not a correct BMP file\n";
        return NULL;
    }
    dataPos = *(int*)&(header[0x0A]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    imageSize = *(int*)&(header[0x22]);
    cout << "width = " << width << " height = " << height << endl;
    if (imageSize == 0)
        imageSize = width * height * 3;
    if (dataPos == 0)
        dataPos = 54;
    unsigned char* bitmap = new unsigned char[imageSize];
    fread(bitmap, 1, imageSize, file);
    fclose(file);

    return bitmap;
}
int initTexture() {
    unsigned char* bitmap;
    glEnable(GL_TEXTURE_2D);

    // Load the BMP file
    bitmap = loadBMP((char*)"green_resized.bmp");
    if (bitmap == NULL) {
        cout << "File open error" << endl;
        return -1;
    }
    cout << "width=" << width << " height=" << height << endl;
    glGenTextures(1, &texID1);
    glBindTexture(GL_TEXTURE_2D, texID1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return 0;
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Aquarium View");
    initFish();
    init();
    
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);
    glutIdleFunc(idle);
    initTexture();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}