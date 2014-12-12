#include "mwindow.h"
#include <QDesktopWidget>
#include <QInputDialog>
#include <QString>
#include <QLineEdit>
#include <QRegExp>
#include "serverinfo.h"

mWindow::mWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QDesktopWidget desktop;
    QRect mainScreenSize = desktop.availableGeometry(desktop.primaryScreen());
    this->setGeometry(mainScreenSize.width()*.1,mainScreenSize.height()*.1, mainScreenSize.width()*.8, mainScreenSize.height()*.8);
    // From ... http://qt-project.org/doc/qt-4.7/qinputdialog.html

    ServerInfo *SI = new ServerInfo;
    SI->show();
    connect(SI, SIGNAL(dServer(QString, int)), this, SLOT(setserver(QString, int)));
    SI->exec();
    myGLWidget = new displayGL(ServerIP, ServerPort, this);
    myGLWidget->resize(800,600);
    myGLWidget->setFocus();
    setCentralWidget(myGLWidget);
}

void mWindow::setserver(QString addr, int port)
{
    qDebug() << "HERE" << endl;
    qDebug() << "IP:" << addr << " AND PORT:" << port <<endl;
    ServerIP =  addr;
    ServerPort = port;
}
