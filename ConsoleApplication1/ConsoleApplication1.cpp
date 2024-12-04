

#include <Windows.h>
#include <glut.h>
#include <glaux.h>
#include <gl.h>      
#include <glu.h>
#include <cmath>
#include <iostream>
void timer(int);
void reshape(int, int);
void keyboard(unsigned char key, int x, int y);
void spkeyboard(int key, int x, int y);
void moving();
void skybox();
bool  keys[256];
GLfloat r = 0, w = 0, d = 0, j = 0, b = 0, n = 0, m = -1;
int ro = 0;
using namespace std;

GLuint skyboxTextures[6];

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 0.0f;
float yaw = -90.0f;
float pitch = 0.0f;



float lamX = 3.0f;
float lamY = 7.0f;
float lamZ = 3.0f;


float ballRadius = 1.0f;
float ballY = 3.0f;
float ballSpeed = 0.0f;
float gravity = 0.003;
float X = 0;
bool me = false;


GLfloat lightpos[] = { 3.0f,3.0f,1.0f,0.0f };
GLfloat lightamp[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightdiff[] = { 0.8f,0.8f,0.8f,1.0f };
GLfloat lightspec[] = { 0.7f,0.7f,0.7f,1.0f };
GLfloat matamp[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat matdif[] = { 0.8f,0.8f,0.8f,1.0f };
GLfloat matspec[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat matshin[] = { 128.0f };


int imgfront, imgback, imgright, imgleft, imgup, imgground;


int initGL(GLvoid) {
    glShadeModel(GL_SMOOTH);              // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);        // Black Background
    glClearDepth(1.0f);                  // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //lighting
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightamp);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightspec);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    //object lighting
    glMaterialfv(GL_FRONT, GL_AMBIENT, matamp);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matdif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matspec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matshin);
    glEnable(GL_COLOR_MATERIAL);

    ////////the sky box
    //glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
    //imgfront = LoadTexture("C:\\Users\\Hp\\Desktop\\box\\front.bmp", 255);
    //imgback = LoadTexture("C:\\Users\\Hp\\Desktop\\box\\back.bmp", 255);
    //imgright = LoadTexture("C:\\Users\\Hp\\Desktop\\box\\right.bmp", 255);
    //imgleft = LoadTexture("C:\\Users\\Hp\\Desktop\\box\\left.bmp", 255);
    //imgup = LoadTexture("C:\\Users\\Hp\\Desktop\\box\\up.bmp", 255);
    //imgground = LoadTexture("C:\\Users\\Hp\\Desktop\\box\\ground.bmp", 255);
    //glPopMatrix();

    ///////the shadow

    //M3DVector3f point[3] = { {-30,-3.9,-20},{-30,-3.9,20},{40,-3.9,20} };
    //m3dGetPlaneEquation(vplane, point[0], point[1], point[2]);

    //m3dMakePlanarShadowMatrix(shadmat, vplane, lightpos);






    return TRUE;
}

float x = 0, y = 0, z = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(n * 90, 1, 0, 0);
    glRotatef(b * 90, 0, 1, 0);
    glTranslatef(cameraX, -6, cameraZ - 15);

    lightpos[0] = lamX;
    lightpos[1] = lamY;
    lightpos[2] = lamZ;
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    //m3dMakePlanarShadowMatrix(shadmat, vplane, lightpos);

    //  skybox();

       ////the lamba
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glColor3ub(255, 0, 0);
    glTranslatef(lamX, lamY, lamZ);
    glutSolidSphere(0.6, 100, 100);
    glPopMatrix();


  






    glutSwapBuffers();

}
//this is a piece of 


int main(int argc, char* argv[]) {
    WNDCLASS  wc;
    // Initialize GLUT
    glutInit(&argc, argv);
    // Set up some memory buffers for our display
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    // Set the window size
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(800, 600);
    // Create the window with the title "Hello,GL"
    glutCreateWindow("open Gl");
    // Bind the two functions (above) to respond when necessary
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(spkeyboard);
    initGL();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    //glutKeyboardFunc();
    // Very important!  This initializes the entry points in the OpenGL driver so we can 
    // call all the functions in the API.
    /*GLenum err = glewInit();
    if (GLEW_OK != err) {
      fprintf(stderr, "GLEW error");
      return 1;
    }*/


    glutMainLoop();
    return 0;
}
//time function
void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}


//reshape function
void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)                    // Prevent A Divide By Zero By
    {
        height = 1;                    // Making Height Equal One
    }

    glViewport(0, 0, width, height);            // Reset The Current Viewport
    glMatrixMode(GL_PROJECTION);            // Select The Projection Matrix
    glLoadIdentity();                  // Reset The Projection Matrix
    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 900.0f);
    glMatrixMode(GL_MODELVIEW);              // Select The Modelview Matrix
    glLoadIdentity();
}


void skybox() {
    ////skybox
    //front
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, imgfront);
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-400, -3.91, -400);
    glTexCoord2d(1, 0);
    glVertex3d(400, -3.91, -400);
    glTexCoord2d(1, 1);
    glVertex3d(400, 400, -400);
    glTexCoord2d(0, 1);
    glVertex3d(-400, 400, -400);
    glEnd();
    glPopMatrix();
    //left  
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, imgright);
    glColor3ub(255, 255, 255);

    glRotatef(90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-402, -4.91, -400);
    glTexCoord2d(1, 0);
    glVertex3d(402, -4.91, -400);
    glTexCoord2d(1, 1);
    glVertex3d(402, 402, -400);
    glTexCoord2d(0, 1);
    glVertex3d(-402, 402, -400);
    glEnd();
    glPopMatrix();
    //right
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, imgleft);
    glColor3ub(255, 255, 255);
    glRotatef(-90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-402, -4.91, -400);
    glTexCoord2d(1, 0);
    glVertex3d(402, -4.91, -400);
    glTexCoord2d(1, 1);
    glVertex3d(402, 402, -400);
    glTexCoord2d(0, 1);
    glVertex3d(-402, 402, -400);
    glEnd();
    glPopMatrix();

    //back
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, imgback);
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2d(1, 0);
    glVertex3d(-400, -3.91, +400);
    glTexCoord2d(0, 0);
    glVertex3d(400, -3.91, +400);
    glTexCoord2d(0, 1);
    glVertex3d(400, 400, +400);
    glTexCoord2d(1, 1);
    glVertex3d(-400, 400, +400);
    glEnd();
    glPopMatrix();
    /////ground
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, imgground);
    glColor3ub(255, 255, 255);
    glRotatef(90, 0, 1, 0);

   
        glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-400, -3.901, 400);
    glTexCoord2d(1, 0);
    glVertex3d(400, -3.901, 400);
    glTexCoord2d(1, 1);
    glVertex3d(400, -3.901, -400);
    glTexCoord2d(0, 1);
    glVertex3d(-400, -3.901, -400);
    glEnd();
    glPopMatrix();
    ////up
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, imgup);
    glColor3ub(255, 255, 255);
    glTranslatef(0, 403.901, 0);
    glRotatef(90, 0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-400, -3.901, -400);
    glTexCoord2d(1, 0);
    glVertex3d(400, -3.901, -400);
    glTexCoord2d(1, 1);
    glVertex3d(400, -3.901, 400);
    glTexCoord2d(0, 1);
    glVertex3d(-400, -3.901, 400);
    glEnd();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);


}
void moving() {

    ballY += ballSpeed;
    ballSpeed -= gravity;

    if (ballY <= -3) {
        X++;
        // std::cout<<"bally"<<ballY<<"......ballspeed"<<ballSpeed<<".........x="<<X<<"\n";
        ballY = -3;
        ballSpeed = -ballSpeed * 0.7;
        if (X > 17) {
            ballSpeed = 0;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    /*case 'w':
        cameraZ -= 0.2 * (sin(yaw * 3.14159 / 180.0));
        cameraX -= 0.2 * (cos(yaw * 3.14159 / 180.0));
        break;

    case 's':
        cameraZ += 0.2 * sin(yaw * 3.14159 / 180.0);
        cameraX += 0.2 * cos(yaw * 3.14159 / 180.0);
        break;*/

    case 'a':
        cameraX += 0.2 * sin(yaw * 3.14159 / 180.0);
        cameraZ += 0.2 * cos(yaw * 3.14159 / 180.0);
        break;

    case 'd':
       cameraX -= 0.2 * sin(yaw * 3.14159 / 180.0);
        cameraZ -= 0.2 * cos(yaw * 3.14159 / 180.0);
        break;
    case 'q':
        cameraY += 0.05f;
        break;
    case 'e':
        cameraY -= 0.05f;
        break;
    case VK_SPACE:
    {
        ballY = 3;
        ballSpeed = 0;
        X = 0;

        me = true;
    }
    break;
    case 'i':
        lamY += 0.02;
        break;
    case 'k':
        lamY -= 0.02;
        break;

    case 'l':
        lamX += 0.02;
        break;
    case 'j':
        lamX -= 0.02;
        break;

    case 'u':
        lamZ += 0.02;
        break;

    case 'o':
        lamZ -= 0.02;
        break;
    case 'h':
        ro += 20;
        break;

    }
}
void spkeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {

        b += 0.01 * cos(0.01);
        //n+=0.04*sin(0.01);
    }
    if (key == GLUT_KEY_LEFT) {

        b -= 0.01 * cos(0.01);
        //  n-=0.04*sin(0.01);
    }

    if (key == GLUT_KEY_UP) {
        n -= 0.01 * cos(0.01);
    }

    if (key == GLUT_KEY_DOWN) {
        n += 0.01 * cos(0.01);
    }


}