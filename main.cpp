#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "robot.h"
//#include "dijekstra.h"
#include "astar.h"

using namespace std;

// Define statements
#define WINDOW_W    500
#define WINDOW_H    500
#define COLUMNS     40
#define ROWS        40
#define FPS         10
// End of Define statements

// Extern variables

// End of extern variables

// Global variables
int isGoalSet = 0;
bool isRobotMove = false;
int mouseX = 0, mouseY = 0;
extern int goalX, goalY;
extern int counter;
// End of global variables

// Callbacks
void display_callback();
void reshape_callback(int, int);
void mouse_callback(int, int, int, int);
void motion_callback(int, int);
void keyboard_callback(unsigned char, int, int);
void timer_callback(int);
// End of Callbacks

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    initGrid(COLUMNS, ROWS);
    //dijkstra_debug();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow("2D Robot Simulator");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutMouseFunc(mouse_callback);
    glutMotionFunc(motion_callback);
    glutKeyboardFunc(keyboard_callback);
    glutTimerFunc(0, timer_callback, 0);
    init();
    glutMainLoop();

    return 0;
}

int cnt = 0;

void display_callback()
{
    astarInit();
    //dijkstraInit();
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawBarrier(mouseX, mouseY);
    drawGoalPosition(goalX, goalY);
    //dijkstra_debug();
    astarCalculate();
    //calculateDijkstra();
    visualizePath();
    if(isRobotMove)
    {
        drawRobot();
    }
    astarFreeParameters();
    //dijkstra_debug();
    //dijkstraFreeParameters();
    glutSwapBuffers();
}

void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW_MATRIX);
}

void mouse_callback(int btn, int state, int x, int y)
{
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
            if(isGoalSet == 1)
            {
                goalX = x;
                goalY = y;
                isGoalSet = 0;
            }else
            {
                mouseX = x;
                mouseY = y;
            }
    }
}

void motion_callback(int x, int y)
{
    mouseX = x;
    mouseY = y;
    drawBarrier(x,y);
}

void keyboard_callback(unsigned char inp, int x, int y)
{
    switch (inp)
    {
    case 'r':
        clearBarriers();
        break;
    case 'g':
        isGoalSet = 1;
        break;
    case 'm':
        isRobotMove = true;
        break;
    }
}

void timer_callback(int )
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer_callback, 0);
}
