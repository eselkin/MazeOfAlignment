#include "moralityserver.h"
#include "threadofmorality.h"
#include <QStringList>
#include <QString>
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

void MoralityServer::getCommand(qint64 PlayerID, QByteArray packetcommand)
{
    // RESPOND TO THE CLIENT REQUEST HERE!
    // Response to the client would be more difficult and would have to have repeating keys for which we can use regular expressions to split
    //    LOCATION::ID1-1,ID2-4,ID3-19 // {socket descriptor that your computer would turn into player 0, 1, 2, ... n players
    //    WINNING ::ID                 // Which socket descriptor won
    //    SCORE   ::ID1-900,ID2-100000 // etc.
    QString incomingcommand(packetcommand);
    QStringList BytesCommand = incomingcommand.split("//",QString::SkipEmptyParts);
    qint16 bytesize(BytesCommand[0].toInt());
    if (BytesCommand[1].size() != bytesize)
        qDebug() << "incorrect packet size!"; // but do nothing... really how big are our packets? 20 bytes?
    QStringList CKeyVal = BytesCommand[1].split("::", QString::SkipEmptyParts);
    switch(CKeyVal[0])
    {
    case "LOCATION":
        break;
    case "WINNING":
        break;
    case "SCORE":
        break;
    }

    QByteArray newPacketCommand(commandString);
    //emit sendCommand(newPacketCommand);
}

void MoralityServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Socket: " << socketDescriptor << " connecting.";
    ThreadOfMorality *thread = new ThreadOfMorality(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(commandToServer(QByteArray)), this, SLOT(getCommand(QByteArray)));
    connect(this, SIGNAL(sendCommand(QByteArray)), thread, SLOT(commandToSocket(QByteArray)));
    descriptors << *socketDescriptor;
    locations << 0;
    thread->start();
}
