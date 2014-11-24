#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "displaygl.h"

class mWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mWindow(QWidget *parent = 0);

signals:

public slots:
private:
    QWidget* centralWidget;
    displayGL* myGLWidget;

};

#endif // MWINDOW_H
