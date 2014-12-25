#include "moralityserver.h"
#include <QThread>
#include <QStringList>
#include <QString>
#include <QMutex>
#include <QDebug>
MoralityServer::MoralityServer(QObject *parent) :
    QTcpServer(parent)
{
}

void MoralityServer::StartServer(int myport)
{
    if (this->listen(QHostAddress::Any, myport))
    {
        qDebug() << "Server Started... at " << serverAddress() << " and port: " << this->serverPort();
    }
    else
    {
        qDebug() << "Server did NOT start...";
    }
}

void MoralityServer::getCommand(int PlayerID, MoralThread *theThread, QByteArray packetcommand)
{
    qDebug() << "GETTING COMMAND FROM THE THREAD" <<endl;
    qDebug() << "COMMAND: " << packetcommand << endl;
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
    QStringList CKeyVal = BytesCommand[1].split("::");
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
        commandString.append(QString::number(PlayerID)); // just broadcast this to all players
    }
    else if (CKeyVal[0] == "SCORE")
    {
        // After winning is received on the server, clients will send a SCORE VALUE...
        // when received from all clients, will emit back in unison

        //        commandString="SCORE::";
        //        commandString.append() NOT SURE ABOUT THIS YET SCORE OR ALIGNMENT
        //        IT COULD BE DISPLAYED SOMEHOW
    }
    else if (CKeyVal[0] == "DAMAGE")
    {
        emit sendCommand(packetcommand); // the same one that came from the client since already in the right format
        return;
    }
    else if (incomingcommand.contains("SOCKETID"))
    {
        commandString="SOCKETID::";
        commandString.append(QString::number(theThread->getSocketDescriptor()));
        QString command;
        command = QString::number(commandString.size()); // packet size
        command.append(tr("//"));
        command.append(commandString);
        QByteArray newPacketCommand;
        newPacketCommand.append(command);
        for (int i =0; i < Morals.size(); i++)
        {
            if (Morals[i]->getSocketDescriptor() == theThread->getSocketDescriptor())
            {
                Morals[i]->commandToSocket(newPacketCommand);
                return;
            }
        }
    }
    else
    {
        return;
    }
    QString command;
    command = QString::number(commandString.size()); // packet size
    command.append(tr("//"));
    command.append(commandString);
    QByteArray newPacketCommand;
    newPacketCommand.append(command);
    for (int i =0; i < Morals.size(); i++)
    {
        Morals[i]->commandToSocket(newPacketCommand);
    }
    qDebug() << "THE PACKET: " << newPacketCommand <<endl;
}

void MoralityServer::removeplayer(int PlayerID)
{
    int i = 0;
    for (; i < descriptors.size() && descriptors[i] != PlayerID ; i++);
    // i is ID location
    QMutex thisMutex;
    thisMutex.lock();
    descriptors.remove(i);
    locations.remove(i);
    thisMutex.unlock();
    // do not send out info of new locations here
    // because seems to happen before socket gets
    // destroyed leading to a crash! Not NULL ptr
    // dereference, but just as bad!

}

void MoralityServer::moveToLocation(int PlayerID, int newloc)
{
    int i = 0;
    for (; i < descriptors.size() && descriptors[i] != PlayerID ; i++);
    // i is ID location in QVector
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
    descriptors.push_back(socketDescriptor);
    locations.push_back(0);
    qDebug() << "Socket: " << socketDescriptor << " connecting.";
    QThread* aThread = new QThread();
    Morals.push_back(new MoralThread(socketDescriptor));
    Morals[Morals.size()-1]->moveToThread(aThread);
    connect(Morals[Morals.size()-1], SIGNAL(destroyed()), aThread, SLOT(quit()));
    connect(this, SIGNAL(sendCommand(QByteArray)), Morals[Morals.size()-1], SLOT(commandToSocket(QByteArray)));
    connect(Morals[Morals.size()-1], SIGNAL(commandToServer(int,MoralThread*,QByteArray)), this, SLOT(getCommand(int,MoralThread*,QByteArray)));
    connect(Morals[Morals.size()-1], SIGNAL(socketdisconnect(int)), this, SLOT(removeplayer(int)));
    connect(aThread, SIGNAL(finished()), aThread, SLOT(deleteLater()));
    connect(aThread, SIGNAL(finished()), this, SLOT(deleteLater()));
}
