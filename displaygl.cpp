#include "displaygl.h"
#include <cmath>
#include <QtOpenGL>
#include <QPainter>
#include <QPaintEvent>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QDebug>
#include <iostream>
#include <QPixmap>
#include <QString>
#include "adjacency.h"
using namespace std;

displayGL::displayGL(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
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
    setAutoFillBackground(false);
    current_direction = WEST;
    current_level = 1;
    current_room = 17;
    init_fp();
}

void displayGL::init_fp()
{
    for(uint i = 0; i < 128; i++)
        key_fptrs[i] = &displayGL::doNothing;
    key_fptrs[Qt::Key_W] = key_fptrs[Qt::Key_8] = &displayGL::moveForward;
    key_fptrs[Qt::Key_S] = key_fptrs[Qt::Key_2] = &displayGL::moveBackward;
    key_fptrs[Qt::Key_A] = key_fptrs[Qt::Key_4] = &displayGL::turnLeft;
    key_fptrs[Qt::Key_D] = key_fptrs[Qt::Key_6] = &displayGL::turnRight;
}

void displayGL::loadTextures()
{
    m_images[0] = convertToGLFormat(QImage("BackWall.png", "PNG"));
    m_images[1] = convertToGLFormat(QImage("Wall.png", "PNG"));
    m_images[2] = convertToGLFormat(QImage("LockedDoor1.png", "PNG"));
    //    m_images[4].load("Locked2.png");
    //    m_images[5].load("Locked3.png");
    //    m_images[6].load("Locked4.png");
    //    m_images[7].load("Locked5.png");
    //    m_images[8].load("Locked6.png");
    //    m_images[9].load("Locked7.png");
    //    m_images[10].load("Locked8.png");
    //    m_images[11].load("Locked9.png");
    //    m_images[12].load("Locked10.png");
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(40, texture_ids);
    for (uint i = 0 ; i < 4; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture_ids[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_images[i].width(), m_images[i].width(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[i].bits());
    }
    // bind the images to the textures
}

void displayGL::initializeGL()
{
    glClearColor(0,0,0,0); // set clear color buffer bit
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    loadTextures();
}

void displayGL::paintEvent(QPaintEvent *event)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    int count_ahead = 0; // forward
    int my_room = current_room;
    int i = 0;

    weights* forward = NULL;
    do {
        my_room = my_room + count_ahead;
        if (current_direction == NORTH)
        {
            drawSideWall(0,checkAhead(my_room,my_room+countAhead(WEST)), i, current_level);
            drawSideWall(1,checkAhead(my_room,my_room+countAhead(EAST)), i, current_level);
        }
        else
            if (current_direction == SOUTH)
            {
                drawSideWall(0,checkAhead(my_room,my_room+countAhead(EAST)), i, current_level);
                drawSideWall(1,checkAhead(my_room,my_room+countAhead(WEST)), i, current_level);
            }
            else
                if (current_direction == EAST)
                {
                    drawSideWall(0,checkAhead(my_room,my_room+countAhead(NORTH)), i, current_level);
                    drawSideWall(1,checkAhead(my_room,my_room+countAhead(SOUTH)), i, current_level);
                }
                else {
                    drawSideWall(0,checkAhead(my_room,my_room+countAhead(SOUTH)), i, current_level);
                    drawSideWall(1,checkAhead(my_room,my_room+countAhead(NORTH)), i, current_level);
                }
        count_ahead = countAhead(current_direction);
        forward = checkAhead(my_room, my_room+count_ahead);
        i++;
    } while (forward && i < 3 && !forward->isDoor()); // stops at a door, can't see through it
    forward && (drawBackWall(i, forward->isDoor(), current_level));
    !forward && (drawBackWall(i, 1, current_level));

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    showInfo(&painter);
    painter.end();
}

void displayGL::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void displayGL::mousePressEvent(QMouseEvent *e)
{
}

void displayGL::keyPressEvent(QKeyEvent *event)
{
    if (event->key() < 128 && event->key() >= 0)
        (this->*(key_fptrs[event->key()]))();
}

void displayGL::showInfo(QPainter *toPaint)
{
    QString Info = tr("Direction: ");

    if (current_direction == NORTH)
        Info.append(tr("NORTH"));
    else
        if (current_direction == SOUTH)
            Info.append(tr("SOUTH"));
        else
            if (current_direction == EAST)
                Info.append(tr("EAST"));
            else
                Info.append(tr("WEST"));
    Info.append( "     Room: ").append(QString::number(current_room));
    QFontMetrics metrics = QFontMetrics(font()); // from http://qt-project.org/doc/qt-4.8/opengl-overpainting.html
    int border = qMax(4, metrics.leading());
    QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125),
                                      Qt::AlignRight | Qt::TextSingleLine, Info);
    toPaint->setRenderHint(QPainter::Antialiasing);
    toPaint->setPen(Qt::white);
    toPaint->drawText((width()-rect.width())/2, border, rect.width(), rect.height(),Qt::AlignRight|Qt::TextSingleLine, Info);
    update();
}



// Basically a draw a vertical trapezoid function
// Whatever calls it will give at what depth it needs to be drawn and what side of the wall it's on
bool displayGL::drawSideWall(bool left_right, weights* access, int start_depth, int level)
{
    double wallstops[6] = {2.0,1.5,1.1,.8,0.4,0}; // anything beyond 5 wall segments out it non-existent in view

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
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    if (access) // if we are a weight... that is: if there is something on the other side of what we're displaying
    {
        glColor3f(.35,.35,.35);
        glBindTexture(GL_TEXTURE_2D, texture_ids[access->isDoor()]);
    }
    else // just a wall
    {
        glColor3f(.1,.1,.1);
        glBindTexture(GL_TEXTURE_2D, texture_ids[0]);
    }

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(start_x,-1.0,-1.*start_depth-1);
    glTexCoord2f(0.0, 1.0); glVertex3f(start_x, 1.0,-1.*start_depth-1);
    glTexCoord2f(1.0, 1.0); glVertex3f(end_x,   1.0,-1.*start_depth-2);
    glTexCoord2f(1.0, 0.0); glVertex3f(end_x,  -1.0,-1.*start_depth-2);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
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

void displayGL::moveForward()
{
    int count_ahead = countAhead(current_direction);
    if ((current_room + count_ahead) > 54 || (current_room + count_ahead) < 9)
        return; // Easy out first, less time to compute bad moves
    weights* testForward;
    if ( (testForward = checkAhead(current_room, current_room + count_ahead)) )
    {
        // This is where we test if we meet the weights requirement!!!!!!!!!!!!!!!!!!!
        //
        // YADA YADA YADA ... player has adequate stats, items, etc.
        // testForward has the list of items we must check against our inventory
        current_room = current_room + count_ahead;
    }
    update();
    updateGL();
}

void displayGL::moveBackward()
{
    int count_ahead = -1 * countAhead(current_direction);
    if ((current_room + count_ahead) > 54 || (current_room + count_ahead) < 9)
        return; // Easy out first, less time to compute bad moves
    weights* testForward;
    if ( (testForward = checkAhead(current_room, current_room + count_ahead)) )
    {
        // This is where we test if we meet the weights requirement!!!!!!!!!!!!!!!!!!!
        //
        // YADA YADA YADA ... player has adequate stats, items, etc.
        // testForward has the list of items we must check against our inventory
        current_room = current_room + count_ahead;
    }
    update();
    updateGL();
}

void displayGL::turnLeft()
{
    current_direction = current_direction == NORTH? WEST : current_direction == WEST? SOUTH : current_direction == SOUTH? EAST : NORTH;
    updateGL();
    update();
}

void displayGL::turnRight()
{
    current_direction = current_direction == NORTH? EAST: current_direction == EAST? SOUTH : current_direction == SOUTH? WEST: NORTH;
    updateGL();
    update();
}

void displayGL::doNothing()
{
    // nada
}

// Precondition: side walls (trapezoids) are drawn and filled with texture?
// Postcondition: back wall is drawn at depth of end of walls that are visible
// Draws a rectangle at the center of the dispaly (dimensions depend on depth, color depends on direction??)
bool displayGL::drawBackWall(int depth, int type, int level)
{
    double wallstops[6] = {2.0,1.5,1.1,.8,0.4,0}; // anything beyond 5 wall segments out it non-existent in view
    if (depth > 5)
        return 0; // we can't draw a wall that far away, it's too dark to see

    double start_x = wallstops[depth];

    glColor3f(level_r[level], level_g[level], level_b[level]); // Get Color from the World
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_ids[type]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-start_x,-1.0,(-1*depth)-1);
    glTexCoord2f(0.0, 1.0); glVertex3f(-start_x, 1.0,(-1*depth)-1);
    glTexCoord2f(1.0, 1.0); glVertex3f( start_x, 1.0,(-1*depth)-1);
    glTexCoord2f(1.0, 0.0); glVertex3f( start_x,-1.0,(-1*depth)-1);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    return 1;
}

