#ifndef DISPLAYGL_H
#define DISPLAYGL_H
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include <QGLWidget>
#include "weights.h"
#include "adjacency.h"

enum DIRECTION { EAST, WEST, NORTH, SOUTH };

class displayGL : public QGLWidget
{
    Q_OBJECT
public:
    //(fo.o)f
    typedef weights* (displayGL::*fptr)(int room);
    explicit displayGL(QWidget *parent = 0);

signals:

public slots:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent( QMouseEvent *e );

protected slots:

protected:

    void drawBackWall(int depth, DIRECTION dir, int level);
    void drawDoor(bool left_right, int start_depth);
    void drawSideWall(bool left_right, bool is_door, int start_depth, int level);

private slots:

private:
    double level_r[7],level_g[7], level_b[7];
    DIRECTION current_direction;
    int current_room;
    fptr check[4];
    weights* checkNorth(int room_number);
    weights* checkWest(int room_number);
    weights* checkEast(int room_number);
    weights* checkSouth(int room_number);

};

#endif // DISPLAYGL_H
