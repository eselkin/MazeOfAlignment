#include "moralityserver.h"
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

void MoralityServer::getCommand(int PlayerID, QByteArray packetcommand)
{
    qDebug() << "GETTING COMMAND FROM THE THREAD" <<endl;
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

    QMutex thisMutex;
    thisMutex.lock();
    int thread_num = threads.size();
    for (int i = 0; i < thread_num; i++)
        threads[i]->commandToSocket(newPacketCommand);
    thisMutex.unlock();
    // Instead of emit, which wasn't getting to the right location and Qt complained even though it is the correct way to do things
    // emit sendCommand(newPacketCommand);
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
    qDebug() << "Socket: " << socketDescriptor << " connecting.";
    ThreadOfMorality *thread = new ThreadOfMorality(socketDescriptor, this);
    threads.push_back(thread); // keep a hold of the thread addresses for broadcast to their slots since the SIGNAL/SLOT WAY CAUSES PROBLEMS
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(commandToServer(int,QByteArray)), this, SLOT(getCommand(int,QByteArray)));
    connect(thread, SIGNAL(socketdisconnect(int)), this, SLOT(removeplayer(int)));
    descriptors.push_back(socketDescriptor);
    locations.push_back(0);
    thread->start();
}
