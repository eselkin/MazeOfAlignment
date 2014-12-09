#include "mwindow.h"
#include <QDesktopWidget>
#include <QInputDialog>
#include <QString>
#include <QLineEdit>


mWindow::mWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QDesktopWidget desktop;
    QRect mainScreenSize = desktop.availableGeometry(desktop.primaryScreen());
    this->setGeometry(mainScreenSize.width()*.1,mainScreenSize.height()*.1, mainScreenSize.width()*.8, mainScreenSize.height()*.8);
    // From ... http://qt-project.org/doc/qt-4.7/qinputdialog.html

    bool OK = false;
    QString Server = "";
    while (!OK && !Server.contains("^([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3})"))
    {
        OK = false;
        Server = QInputDialog::getText(this, tr("Input Server IP address:"), tr("IP address:"), QLineEdit::Normal,  QDir::home().dirName(), &OK);
    }
    myGLWidget = new displayGL(Server, 9966, this);
    myGLWidget->resize(800,600);
    myGLWidget->setFocus();
    setCentralWidget(myGLWidget);
}
