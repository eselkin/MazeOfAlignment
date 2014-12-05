#include <iostream>
#include <QApplication>
#include <QGLWidget>
#include <QTimerEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <ctime>
#include <QFile>
//#include <QSound>
#include "mwindow.h"


using namespace std;
int main(int argc, char** argv)
{
    srand(time(NULL));
    //    QSound sound("01.wav");
    //    sound.play();
    QApplication ThisApp(argc, argv);
    mWindow MAZEGAME;
    MAZEGAME.show();
    return ThisApp.exec(); // enters a loop // done running
}

