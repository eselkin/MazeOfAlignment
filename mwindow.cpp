#include "mwindow.h"
#include <QDesktopWidget>

mWindow::mWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QDesktopWidget desktop;
    QRect mainScreenSize = desktop.availableGeometry(desktop.primaryScreen());

    this->setGeometry(mainScreenSize.width()*.1,mainScreenSize.height()*.1, mainScreenSize.width()*.8, mainScreenSize.height()*.8);
    this->setFixedSize(this->width(),this->height());
    centralWidget = new QWidget(this); // this is parent
    centralWidget->setObjectName(QString::fromUtf8("centralWidget")); // The only Qwidget.
    myGLWidget = new displayGL(centralWidget);
    centralWidget->resize(this->width(),this->height());
    myGLWidget->resize(mainScreenSize.width()*.1,mainScreenSize.height()*.1, mainScreenSize.width()*.8, mainScreenSize.height()*.8);
}
