#ifndef MWINDOW_H
#define MWINDOW_H

#include <QFile>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QFileDialog>
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
    QVBoxLayout* WindowLayout;
    displayGL* myGLWidget;
    QMenuBar* menu;
    QMenu* fileMenu;
    QString ServerIP;
    int ServerPort;
};

#endif // MWINDOW_H
