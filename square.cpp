///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
// 
// Sumanta Guha.
// Added documentation by Tom Kelliher.
///////////////////////////////////
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include <iostream>

GLint Wx = 500;
GLint Wy = 500;

GLfloat moveSpeed = .1;

GLfloat cameraSpeed = 5;
GLdouble cameraPos[3] = {{0}, {0}, {0}};

void MyInit()
{
    glClearColor(0,0,0,1);
    glColor3f(1,0,0);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);   
    glMatrixMode(GL_MODELVIEW);
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
    glClearColor (0,0,0,1);
    
    glBegin(GL_POLYGON);
        glVertex3fv(A);
        glVertex3fv(B);
        glVertex3fv(C);
        glVertex3fv(D);
    glEnd();
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
    glColor3f(1,0,0);
    Face(V0, V1, V2, V3); //Front
    
    glColor3f(0,1,0);
    Face(V4, V5, V6, V7); //Back
    
    glColor3f(0,0,1);
    Face(V0, V3, V7, V4); //Left
    
    glColor3f(1,0,1);
    Face(V1, V2, V6, V5); //Right
    
    glColor3f(1,1,0);
    Face(V0, V1, V5, V4); //Top
    
    glColor3f(1,1,1);
    Face(V3, V2, V6, V7); //Botom
}

// Drawing routine.
void Start(void)
{
    //Initialize Verticies for Cube
    GLfloat V[8][3] = {
        {-0.5, 0.5, 0.5},
        { 0.5, 0.5, 0.5},
        { 0.5,-0.5, 0.5},
        {-0.5,-0.5, 0.5},
        
        {-0.5, 0.5,-0.5},
        { 0.5, 0.5,-0.5},
        { 0.5,-0.5,-0.5},
        {-0.5,-0.5,-0.5}
                            };
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, cameraPos[0], cameraPos[1], cameraPos[2], 0, 1, 0);
    
    Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);

    glutSwapBuffers();
}

// OpenGL window reshape routine.
// w and h are the width and height of the window in pixels.
void resize(int w, int h)
{
    // Use the entire window.  See the documentation for glViewport
    // for the interpretation of the parameters.
    glViewport(0, 0, w, h);
}

// Mouse
/*void moveMouse(int x, int y)
{
    glutPostRedisplay();
}*/
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    //W
    case 119:
        cameraPos[0] = cameraPos[2] + moveSpeed;
        break;
    //A
    case 97:
        cameraPos[0] = cameraPos[0] - moveSpeed;
        break;
    //S
    case 115:
        cameraPos[0] = cameraPos[2] - moveSpeed;
        break;
    //D
    case 100:
        cameraPos[0] = cameraPos[0] + moveSpeed;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;   
    }
    
    glutPostRedisplay();
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    // We're using OpenGL version 3.1 in compatibility mode.
    // I.e., the fixed function pipeline.
    glutInitContextVersion(3, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Use double-buffering and RGB color.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowSize(Wx, Wy);
    glutInitWindowPosition(100, 100);

    
    // Create the window and give it a title.
    glutCreateWindow("square.cpp");
    
    
    //glutFullScreen();
    // Register callback functions.
    // Called to render the scene.  Do not call the
    // callback directly.  Let GLUT decide when to do so.
    glutDisplayFunc(Start);

    // Called when the window is resized.
    glutReshapeFunc(resize);
    
    // Call upon keyboard input.
    glutKeyboardFunc(keyInput);
    //Mouse
    //glutPassiveMotionFunc(moveMouse);
    
    glewExperimental = GL_TRUE;
    glewInit();
    MyInit();

    // GLUT enters its event processing loop.  It will not return.
    glutMainLoop();

    return 0;
}
