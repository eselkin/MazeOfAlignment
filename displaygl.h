#ifndef DISPLAYGL_H
#define DISPLAYGL_H
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include <QGLWidget>
#include <QPixmap>
#include "weights.h"
#include "adjacency.h"

enum DIRECTION { EAST, WEST, NORTH, SOUTH };

class displayGL : public QGLWidget
{
    Q_OBJECT
public:
    //(fo.o)f
    typedef weights* (displayGL::*fptr)(int room, int next);
    explicit displayGL(QWidget *parent = 0);

signals:

public slots:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent( QMouseEvent *e );

protected slots:

protected:

    void loadTextures();
    bool drawBackWall(int depth, int type, int level);
    bool drawDoor(bool left_right, int start_depth);
    bool drawSideWall(bool left_right, int is_door, int start_depth, int level);

private slots:

private:
    QPixmap m_images[40];
    GLuint m_texture_ids[40]; // Texture IDS
    double level_r[7],level_g[7], level_b[7];
    DIRECTION current_direction;
    int current_room, current_level;
    Adjacency adjacencyTable;
    weights* checkAhead(int room_number, int next_room);
    int countAhead(DIRECTION dir);

};

#endif // DISPLAYGL_H
