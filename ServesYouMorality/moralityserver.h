#ifndef MORALITYSERVER_H
#define MORALITYSERVER_H
#include "threadofmorality.h"
#include <QTcpServer>
#include <QDebug>
#include <QVector>



///
/// The MoralityServer class...
/// This is the server, run from a parent with an instance of it and then
/// run it with the start server... listening on a 8byte or less port that
/// you pass the StartServer(qint8) member function
///
/// From the main server thread connections are made and pushed to threads
/// where a socket is formed and connected. Details about the thread are handled
/// in threadofmorality.h
///
/// In incommingConnection member function a signal/slot connections are bound
/// so when text to the server is emitted by the thread's socket (connection from client)
/// We interpret that here as a command that must meet some specification.
/// The specifications are lengthofcommandprefixanddata//COMMANDPREFIX::DATA
///
///

class MoralityServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MoralityServer(QObject *parent = 0);
    void StartServer(int port);

signals:
    void sendCommand(QByteArray packetcommand);

public slots:
    void getCommand(int PlayerID, ThreadOfMorality *theThread,  QByteArray packetcommand);
    void removeplayer(int PlayerID);

protected:
    void incomingConnection(int socketDescriptor);
    void moveToLocation(int PlayerID, int newloc);
    QString getLocations();

private:
    qint32 num_clients;
    qint8 level;                 // everyone is on one level
    QVector< ThreadOfMorality *> threads; // vector of thread pointers
    QVector<int> descriptors; // when joined, order matters for locations
    QVector<int>  locations;   // after joining, a 0 location is added, then replaced when user is placed into a room and submits it to the server
};

#endif // MORALITYSERVER_H
