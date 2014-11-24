#ifndef DISPLAYGL_H
#define DISPLAYGL_H

#include <QGLWidget>
enum DIRECTION { EAST, WEST, NORTH, SOUTH };

class displayGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit displayGL(QWidget *parent = 0);

signals:

public slots:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent( QMouseEvent *e );

protected slots:

protected:

    void drawBackWall(int depth, DIRECTION dir);
    void drawDoor(bool left_right, int start_depth);
    void drawSideWall(bool left_right, bool is_door, int start_depth);

private slots:

private:
    double level_r[7],level_g[7], level_b[7];

};

#endif // DISPLAYGL_H
