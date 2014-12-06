#include "moralityserver.h"
#include <QStringList>
#include <QString>
#include <QMutex>
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
    if (BytesCommand[1].size() != bytesize)  // no it's not really bytes
        qDebug() << "incorrect packet size!"; // but do nothing... really how big are our packets? 20 bytes?
    QStringList CKeyVal = BytesCommand[1].split("::", QString::SkipEmptyParts);
    QString commandString;
    if (CKeyVal[0] == "LOCATION")
    {
        commandString="LOCATION::";
        qint8 newlocation = CKeyVal[1].toInt();
        setLocation(PlayerID, newlocation);
        commandString.append(getLocations());
    }
    else if (CKeyVal[0] == "WINNING")
    {
        commandString="WINNING::";
        commandString.append(QString::number(PlayerID));
    }
    else if (CKeyVal[0] == "SCORE")
    {
        //        commandString="SCORE::";
        //        commandString.append() NOT SURE ABOUT THIS YET SCORE OR ALIGNMENT
        //        IT COULD BE DISPLAYED SOMEHOW
    }
    else
    {
        return;
    }
    QDataStream dataStream;
    dataStream << QString::number(commandString.size());
    dataStream << tr("//").toAscii();
    dataStream << commandString.toAscii();
    QByteArray newPacketCommand;
    dataStream >> newPacketCommand ;
    emit sendCommand(newPacketCommand);
}

QString MoralityServer::setLocation(qint64 PlayerID, qint8 newlocation)
{
    QMutex thisMutex;
    thisMutex.lock();
    int i = 0;
    for (; i < descriptors.size() && descriptors[i] != PlayerID ; i++);
    // i is ID location
    locations[i] = newlocation;
    thisMutex.unlock();
}

QString MoralityServer::getLocations()
{
    QString templocations;
    QMutex thisMutex;
    for (int i = 0; i < descriptors.size(); i++)
    {
        if (i != 0)
            templocations.append(tr(","));
        thisMutex.lock(); // block access so we have the most relevant locations and descriptors
        templocations.append(QString::number(descriptors[i]));
        templocations.append(tr("-"));
        templocations.append(QString::number(locations[i]));
        thisMutex.unlock();
    }
    return templocations;
}

void MoralityServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Socket: " << *socketDescriptor << " connecting.";
    ThreadOfMorality *thread = new ThreadOfMorality(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(commandToServer(qint64,QByteArray)), this, SLOT(getCommand(qint64,QByteArray)));
    connect(this, SIGNAL(sendCommand(QByteArray)), thread, SLOT(commandToSocket(QByteArray)));
    descriptors << *socketDescriptor;
    locations << 0;
    thread->start();
}
