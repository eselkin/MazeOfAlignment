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

private slots:

private:


};

#endif // DISPLAYGL_H
