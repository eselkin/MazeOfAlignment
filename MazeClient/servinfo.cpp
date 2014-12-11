#include "servinfo.h"

servinfo::servinfo(QWidget *parent) :
    QMainWindow(parent)
{
    theLayout = new QGridLayout(this);
    ServerAddress = new QLineEdit;
    ServerPort = new QLineEdit;

    SLabel = new QLabel("Server Address");
    PLabel = new QLabel("Server Port");

    P_OK = new QPushButton("OK");
    P_CANCEL = new QPushButton("CANCEL");


    this->resize(400, 200);
    theLayout->addWidget(ServerAddress, 1,1,1,2);
    theLayout->addWidget(ServerPort, 1,3,1,1);
    theLayout->addWidget(SLabel, 2,1,1,1);
    theLayout->addWidget(PLabel, 2,3,1,1);
    theLayout->addWidget(P_OK, 3,2,1,1);
    theLayout->addWidget(P_CANCEL, 3,3,1,1);

    connect(P_OK, SIGNAL(clicked()), this, SLOT(OK_PUSHED()));
    connect(P_CANCEL, SIGNAL(clicked()), this, SLOT(CANCEL_PUSHED()));

}
void servinfo::OK_PUSHED()
{
    //emit dServer(ServerAddress->text(), ServerPort->text().toInt());
    this->hide();
}

void servinfo::CANCEL_PUSHED()
{
    ServerAddress->setText("127.0.0.1");
    ServerPort->setText("9966");
    //emit dServer(ServerAddress->text(), ServerPort->text().toInt());
    this->hide();
}
