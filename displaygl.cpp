#include "displaygl.h"
#include <cmath>
#include <iostream>
#include "adjacency.h"
using namespace std;

displayGL::displayGL(QWidget *parent) :
    QGLWidget(parent)
{
    check[NORTH] = &displayGL::checkNorth;
    check[SOUTH] = &displayGL::checkSouth;
    check[EAST] = &displayGL::checkEast;
    check[WEST] = &displayGL::checkWest;

    double r_init = 0.0;
    double g_init = 0.1;
    double b_init = 0.1;
    for (uint i = 0; i < 7; i++)
    {
        (i%2) && (r_init+=0.25);
        (i%3) && (g_init+=0.1);
        (i%5) && (b_init+=0.25);
        level_r[i] = r_init;
        level_g[i] = g_init;
        level_b[i] = b_init;
    }
    current_direction = NORTH;
}

void displayGL::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0,0,0,0); // set clear color buffer bit
}

void displayGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // from clear color above
    glLoadIdentity();

    //
    // Turning allows us to calculate what is ahead of us
    //


//    weights* forward = check[current_direction](current_room);
//    //int count_ahead = current_direction == NORTH? 1 : current_direction == WEST ? -8 : current_direction == SOUTH? -1 : 8;


//    //(current_direction == NORTH) && drawSideWall(0, check[WEST](current_room)->isWall(), 0, 2) && drawSideWall(0, check[EAST](current_room), 0, 2);
//    drawSideWall(1, 0, 1, 1);
//    if (forward)
//    {
//        drawSideWall(0, 0, 0, 2);
//        drawSideWall(0, 0, 1, 1);
//        weights* next = check[current_direction](current_room + count_ahead);
//        if (next)
//        {

//        }
//    }

    drawSideWall(0, 0, 2, 1);
    drawSideWall(1, 0, 0, 2);
    drawDoor(1, 1);
    drawSideWall(1, 0, 2, 1);
    drawBackWall(3, WEST, 0);
}

void displayGL::resizeGL(int w, int h)
{

}

void displayGL::mousePressEvent(QMouseEvent *e)
{

}

// Basically a draw a vertical trapezoid function
// Whatever calls it will give at what depth it needs to be drawn and what side of the wall it's on
void displayGL::drawSideWall(bool left_right, bool is_door, int start_depth, int level)
{
    double wallstops[6] = {1.0,0.5,0.35,0.25,0,0}; // anything beyond 5 wall segments out it non-existent in view

    /*
     *  |\     |     /|
     *  | \    |    / |
     *  |  |\  |  /|  |
     *  |  | |-+-| |  |
     * -+--+-+-2-+1+-0+-
     *  |  | |-+-| |  |
     *  |  |/__|__\|  |
     *  | /    |    \ |
     *  |/_____|_____\|
     *         |
     */

    double start_x = wallstops[start_depth] * (left_right ? 1 : -1);
    double end_x = wallstops[start_depth+1] * (left_right ? 1 : -1);
    double up_start_y = abs(start_x);
    double up_end_y = abs(end_x);
    if (is_door)
        glColor3f(.03,.03,.03);
    else
        glColor3f(level_r[level], level_g[level], level_b[level]); // Get Color from the World
    glBegin(GL_QUADS);
    glVertex3f(start_x, up_start_y,0);
    glVertex3f(end_x, up_end_y,0);
    glVertex3f(end_x, -1.0*up_end_y,0);
    glVertex3f(start_x, -1.0*up_start_y,0);
    glEnd();
    glColor3f(0,0,0); // Get Color from the World
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex3f(start_x, up_start_y,0);
    glVertex3f(end_x, up_end_y,0);
    glVertex3f(end_x, -1.0*up_end_y,0);
    glVertex3f(start_x, -1.0*up_start_y,0);
    glEnd();
}

weights *displayGL::checkNorth(int room_number)
{

}

weights *displayGL::checkWest(int room_number)
{

}

weights *displayGL::checkEast(int room_number)
{

}

weights *displayGL::checkSouth(int room_number)
{

}


// Precondition: side walls (trapezoids) are drawn and filled with texture?
// Postcondition: back wall is drawn at depth of end of walls that are visible
// Draws a rectangle at the center of the dispaly (dimensions depend on depth, color depends on direction??)
void displayGL::drawBackWall(int depth, DIRECTION dir, int level)
{
    double wallstops[6] = {1.0,0.5,0.35,0.25,0,0}; // anything beyond 5 wall segments out it non-existent in view
    if (depth > 5)
        return; // we can't draw a wall that far away, it's too dark to see
    double start_x = wallstops[depth];
    glColor3f(level_r[level], level_g[level], level_b[level]); // Get Color from the World
    glBegin(GL_QUADS);
    glVertex3f(start_x, start_x,0);
    glVertex3f(-1*start_x, start_x,0);
    glVertex3f(-1*start_x, -1.0*start_x,0);
    glVertex3f(start_x, -1.0*start_x,0);
    glEnd();
}

void displayGL::drawDoor(bool left_right, int start_depth)
{
    drawSideWall(left_right, 1, start_depth, 0);
}
