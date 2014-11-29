#ifndef DISPLAYGL_H
#define DISPLAYGL_H
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#include <QGLWidget>
#include <QImage>
#include <QKeyEvent>
#include <QMouseEvent>
#include "weights.h"
#include "adjacency.h"

enum DIRECTION { EAST, WEST, NORTH, SOUTH };

class displayGL : public QGLWidget
{
    Q_OBJECT
public:
    //(fo.o)f
    typedef void (displayGL::*fptr)();
    explicit displayGL(QWidget *parent = 0);
    ~displayGL();
signals:

public slots:
    void initializeGL();
    //void paintGL();
    void resizeGL(int w, int h);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent( QMouseEvent *e );
    void keyPressEvent(QKeyEvent *e);
    void showInfo(QPainter *toPaint);

protected slots:

protected:
    void init_fp();
    void loadTextures();
    bool drawBackWall(int depth, int type, int level);
    bool drawDoor(bool left_right, int start_depth);
    bool drawSideWall(bool left_right, weights *access, int start_depth, int level);

private slots:

private:
    QImage m_images[40];
    GLuint texture_ids[40]; // Texture IDS
    double level_r[7],level_g[7], level_b[7];
    DIRECTION current_direction;
    int current_room, current_level;
    Adjacency adjacencyTable;
    weights* checkAhead(int room_number, int next_room);
    int countAhead(DIRECTION dir);
    fptr key_fptrs[128];
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void PickUpItem();
    void DropItem();
    bool in_inventory, in_rm_inventory;
    void doNothing();
};

#endif // DISPLAYGL_H
