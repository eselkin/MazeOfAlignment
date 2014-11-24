#include "displaygl.h"
#include <cmath>

displayGL::displayGL(QWidget *parent) :
    QGLWidget(parent)
{
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

}

void displayGL::resizeGL(int w, int h)
{

}

void displayGL::mousePressEvent(QMouseEvent *e)
{

}

// Basically a draw a vertical trapezoid function
// Whatever calls it will give at what depth it needs to be drawn and what side of the wall it's on
void displayGL::drawSideWall(bool left_right, bool is_door, int start_depth)
{
    double wallstops[6] = {1.0,0.6,0.4,0.2,0.1,0}; // anything beyond 5 wall segments out it non-existent in view

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

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(start_x, up_start_y,0);
        glTexCoord2f(0,0);
        glVertex3f(end_x, up_end_y,0);
        glTexCoord2f(1,0);
        glVertex3f(start_x, -1.0*up_start_y,0);
        glTexCoord2f(1,1);
        glVertex3f(end_x, -1.0*up_end_y,0);
    glEnd();



}


// Precondition: side walls (trapezoids) are drawn and filled with texture?
// Postcondition: back wall is drawn at depth of end of walls that are visible
// Draws a rectangle at the center of the dispaly (dimensions depend on depth, color depends on direction??)
void displayGL::drawBackWall(int depth, DIRECTION dir)
{
    if (depth >= 5)
        return; // we can't draw a wall that far away, it's too dark to see


}

void displayGL::drawDoor(bool left_right, int start_depth)
{

}
