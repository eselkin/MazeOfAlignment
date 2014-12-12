#include "serverinfo.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
ServerInfo::ServerInfo()
{
    theLayout = new QGridLayout(this);
    ServerAddress = new QLineEdit;
    ServerPort = new QLineEdit;

    SLabel = new QLabel("Server Address", this);
    PLabel = new QLabel("Port", this);

    P_OK = new QPushButton("OK", this);
    P_CANCEL = new QPushButton("CANCEL", this);


    this->resize(300, 100);
    theLayout->addWidget(ServerAddress, 1,1,1,3);
    theLayout->addWidget(ServerPort, 1,4,1,1);
    theLayout->addWidget(SLabel, 2,1,1,1);
    theLayout->addWidget(PLabel, 2,4,1,1);
    theLayout->addWidget(P_OK, 3,2,1,1);
    theLayout->addWidget(P_CANCEL, 3,3,1,1);

    connect(P_OK, SIGNAL(clicked()), this, SLOT(ok_pushed()));
    connect(P_CANCEL, SIGNAL(clicked()), this, SLOT(cancel_pushed()));
    ServerAddress->setFocus();
}


void ServerInfo::ok_pushed()
{
    QRegExp ip_exp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    if (ip_exp.indexIn(ServerAddress->text()) == -1)
        QMessageBox::information(this, "Use a valid IP", "Please enter a valid IP address for the server.", QMessageBox::Ok);
    else
    {
        emit dServer(ServerAddress->text(), ServerPort->text().toInt());
        this->hide();
    }
}

void ServerInfo::cancel_pushed()
{
    ServerAddress->setText("127.0.0.1");
    ServerPort->setText("9966");
    emit dServer(ServerAddress->text(), ServerPort->text().toInt());
    this->hide();
}
