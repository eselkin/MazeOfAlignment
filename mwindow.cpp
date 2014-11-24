#include "mwindow.h"
#include <QDesktopWidget>

mWindow::mWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QDesktopWidget desktop;
    QRect mainScreenSize = desktop.availableGeometry(desktop.primaryScreen());
    this->setGeometry(mainScreenSize.width()*.1,mainScreenSize.height()*.1, mainScreenSize.width()*.8, mainScreenSize.height()*.8);
    myGLWidget = new displayGL(this);
    myGLWidget->resize(800,600);
    setCentralWidget(myGLWidget);
}
