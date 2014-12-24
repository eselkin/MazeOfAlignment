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
    // From ... http://qt-project.org/doc/qt-4.7/qinputdialog.html
    ServerInfo *SI = new ServerInfo;
    SI->show();
    connect(SI, SIGNAL(dServer(QString, int)), this, SLOT(setserver(QString, int)));
    SI->exec();

    centralWidget = new QWidget(this);
    WindowLayout  = new QVBoxLayout(centralWidget);
    myGLWidget = new displayGL(ServerIP, ServerPort, centralWidget);
    centralWidget->setMinimumSize(mainScreenSize.width()*.8,mainScreenSize.height()*.8);
    myGLWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    menu = new QMenuBar(centralWidget);
    fileMenu = new QMenu("&File",menu);
    menu->addMenu(fileMenu);

    setCentralWidget(centralWidget);
    centralWidget->resize(this->width(),this->height());
    myGLWidget->setGeometry(0,30,centralWidget->width(),centralWidget->height()-30);
    resize(mainScreenSize.width(), mainScreenSize.height());
    myGLWidget->setFocus();
}

void mWindow::setserver(QString addr, int port)
{
    qDebug() << "HERE" << endl;
    qDebug() << "IP:" << addr << " AND PORT:" << port <<endl;
    ServerIP =  addr;
    ServerPort = port;
}
