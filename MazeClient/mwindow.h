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
    void setserver(QString addr, int port);

private:
    QWidget* centralWidget;
    displayGL* myGLWidget;
    QString ServerIP;
    int ServerPort;
};

#endif // MWINDOW_H
