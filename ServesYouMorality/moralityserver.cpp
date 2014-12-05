#include "moralityserver.h"
#include "threadofmorality.h"

MoralityServer::MoralityServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MoralityServer::StartServer()
{
    if (this->listen(QHostAddress::Any, 9966))
    {
        qDebug() << "Server Started...";
    }
    else
    {
        qDebug() << "Server did NOT start...";
    }
}

void MoralityServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Socket: " << socketDescriptor << " connecting.";
    ThreadOfMorality *thread = new ThreadOfMorality(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    descriptors << *socketDescriptor;
    locations << 0;
    thread->start();
}
