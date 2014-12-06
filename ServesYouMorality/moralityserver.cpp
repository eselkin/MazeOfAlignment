#include "moralityserver.h"
#include <QStringList>
#include <QString>
#include <QMutex>
#include <QDebug>
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
    if (!incomingcommand.contains("//") || !incomingcommand.contains("::"))
        return; // DONT DO ANYTHING WITH EMPTY LINES
    QStringList BytesCommand = incomingcommand.split("//",QString::SkipEmptyParts);
    qint16 bytesize(BytesCommand[0].toInt());
    //    if (BytesCommand[1].size() != bytesize)  // no it's not really bytes
    //        qDebug() << "incorrect packet size!"; // but do nothing... really how big are our packets? 20 bytes?
    QStringList CKeyVal = BytesCommand[1].split("::", QString::SkipEmptyParts);
    QString commandString;
    if (CKeyVal[0] == "LOCATION")
    {
        commandString="LOCATION::";
        qDebug() << CKeyVal[1] << endl;
        int newlocation = CKeyVal[1].toInt();
        qDebug() << newlocation << endl;
        moveToLocation(PlayerID, newlocation);
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
    QString command;
    command = QString::number(commandString.size());
    command.append(tr("//"));
    command.append(commandString);
    QByteArray newPacketCommand;
    newPacketCommand.append(command);
    qDebug() << "THE PACKET: " << newPacketCommand <<endl;
    emit sendCommand(newPacketCommand);
}

void MoralityServer::moveToLocation(qint64 PlayerID, int newloc)
{
    int i = 0;
    for (; i < descriptors.size() && descriptors[i] != PlayerID ; i++);
    // i is ID location
    QMutex thisMutex;
    thisMutex.lock();
    locations[i] = newloc;
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

void MoralityServer::incomingConnection(int socketDescriptor)
{
    qDebug() << "Socket: " << socketDescriptor << " connecting.";
    ThreadOfMorality *thread = new ThreadOfMorality(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(commandToServer(qint64,QByteArray)), this, SLOT(getCommand(qint64,QByteArray)));
    connect(this, SIGNAL(sendCommand(QByteArray)), thread, SLOT(commandToSocket(QByteArray)));
    descriptors.push_back(socketDescriptor);
    locations.push_back(0);
    thread->start();
}
