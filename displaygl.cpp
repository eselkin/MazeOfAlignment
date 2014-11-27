#include "displaygl.h"
#include <cmath>
#include <QtOpenGL>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <QDebug>
#include <iostream>
#include <QPixmap>
#include "adjacency.h"
using namespace std;

displayGL::displayGL(QWidget *parent) :
    QGLWidget(parent)
{

    double r_init = 0.1;
    double g_init = 0.3;
    double b_init = 0.3;
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
    current_room = 9;
    loadTextures();

}

void displayGL::loadTextures()
{
    glEnable(GL_TEXTURE_2D);
    m_images[0].load("BackWall.png");
    m_images[1].load("LeftWall.png");
    m_images[2].load("UnlockedDoor.png");
    m_images[3].load("Locked1.png");
    m_images[4].load("Locked2.png");
    m_images[5].load("Locked3.png");
    m_images[6].load("Locked4.png");
    m_images[7].load("Locked5.png");
    m_images[8].load("Locked6.png");
    m_images[9].load("Locked7.png");
    m_images[10].load("Locked8.png");
    m_images[11].load("Locked9.png");
    m_images[12].load("Locked10.png");
    glGenTextures(40, m_texture_ids);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,m_images[0].width(), m_images[0].height() , GL_RGB, GL_UNSIGNED_BYTE, &m_images[0]);
    // THIS SHOULD WORK BUT IT'S NOT!
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

    int count_ahead = 0; // forward
    int my_room = current_room;
    int i = 0;

    weights* forward = NULL;
    do {
        my_room = my_room + count_ahead;
        if (current_direction == NORTH)
        {
            drawSideWall(0,checkAhead(my_room,my_room+countAhead(WEST))->isDoor(), i, current_level);
            drawSideWall(1,checkAhead(my_room,my_room+countAhead(EAST))->isDoor(), i, current_level);
        }
        else
            if (current_direction == SOUTH)
            {
                drawSideWall(0,checkAhead(my_room,my_room+countAhead(EAST))->isDoor(), i, current_level);
                drawSideWall(1,checkAhead(my_room,my_room+countAhead(WEST))->isDoor(), i, current_level);
            }
            else
                if (current_direction == EAST)
                {
                    drawSideWall(0,checkAhead(my_room,my_room+countAhead(NORTH))->isDoor(), i, current_level);
                    drawSideWall(1,checkAhead(my_room,my_room+countAhead(SOUTH))->isDoor(), i, current_level);
                }
                else {
                    drawSideWall(0,checkAhead(my_room,my_room+countAhead(SOUTH))->isDoor(), i, current_level);
                    drawSideWall(1,checkAhead(my_room,my_room+countAhead(NORTH))->isDoor(), i, current_level);
                }
        count_ahead = countAhead(current_direction);
        forward = checkAhead(my_room, my_room+count_ahead);
        i++;
    } while (forward && i < 3 && !forward->isDoor()); // stops at a door, can't see through it
    forward && (drawBackWall(i, forward->isDoor(), current_level));
    !forward && (drawBackWall(i, 0, current_level));
}

void displayGL::resizeGL(int w, int h)
{

}

void displayGL::mousePressEvent(QMouseEvent *e)
{

}

// Basically a draw a vertical trapezoid function
// Whatever calls it will give at what depth it needs to be drawn and what side of the wall it's on
bool displayGL::drawSideWall(bool left_right, int is_door, int start_depth, int level)
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

    glEnable( GL_TEXTURE_2D );

    glBegin(GL_QUADS);
    glTexCoord3f(0.0,0.0,0.0); glVertex3f(start_x, up_start_y,0);
    glVertex3f(end_x, up_end_y,0);
    glVertex3f(end_x, -1.0*up_end_y,0);
    glVertex3f(start_x, -1.0*up_start_y,0);
    glEnd();
    glDisable( GL_TEXTURE_2D );

    glColor3f(0,0,0); // Get Color from the World
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex3f(start_x, up_start_y,0);
    glVertex3f(end_x, up_end_y,0);
    glVertex3f(end_x, -1.0*up_end_y,0);
    glVertex3f(start_x, -1.0*up_start_y,0);
    glEnd();

    return 1;
}

weights *displayGL::checkAhead(int room_number, int next_room)
{
    return adjacencyTable.getWeight(room_number, next_room, current_level);
}

int displayGL::countAhead(DIRECTION dir)
{
    return dir == NORTH? 1 : dir == WEST ? -8 : dir == SOUTH? -1 : 8;
}

// Precondition: side walls (trapezoids) are drawn and filled with texture?
// Postcondition: back wall is drawn at depth of end of walls that are visible
// Draws a rectangle at the center of the dispaly (dimensions depend on depth, color depends on direction??)
bool displayGL::drawBackWall(int depth, int type, int level)
{
    double wallstops[6] = {1.0,0.5,0.35,0.25,0,0}; // anything beyond 5 wall segments out it non-existent in view
    if (depth > 5)
        return 0; // we can't draw a wall that far away, it's too dark to see
    double start_x = wallstops[depth];
    glColor3f(level_r[level], level_g[level], level_b[level]); // Get Color from the World
    glBegin(GL_QUADS);
    glVertex3f(start_x, start_x,0);
    glVertex3f(-1*start_x, start_x,0);
    glVertex3f(-1*start_x, -1.0*start_x,0);
    glVertex3f(start_x, -1.0*start_x,0);
    glEnd();
    return 1;
}

