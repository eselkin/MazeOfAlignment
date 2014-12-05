#include "moralityserver.h"

MoralityServer::MoralityServer(QObject *parent) :
    QTcpServer(parent)
{
    PoolOfMorality = new QThreadPool(this);
    PoolOfMorality->setMaxThreadCount(6); // set this

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

void MoralityServer::incomingConnection(int handle)
{
    RunnableMaze* task = new RunnableMaze;
    task->setAutoDelete(true);
    task->setSocketDesc(handle);
    // connection requests
    PoolOfMorality->start(task);
}
