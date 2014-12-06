#ifndef MORALITYSERVER_H
#define MORALITYSERVER_H
#include "threadofmorality.h"
#include <QTcpServer>
#include <QDebug>
#include <QVector>

class MoralityServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MoralityServer(QObject *parent = 0);
    void StartServer();

signals:
    void sendCommand(QByteArray packetcommand);

public slots:
    void getCommand(qint64 PlayerID,  QByteArray packetcommand);

protected:
    void incomingConnection(int socketDescriptor);
    void moveToLocation(qint64 PlayerID, int newloc);
    QString getLocations();

private:
    qint32 num_clients;
    qint8 level;                 // everyone is on one level
    QVector<qint64> descriptors; // when joined, order matters for locations
    QVector<int>  locations;   // after joining, a 0 location is added, then replaced when user is placed into a room and submits it to the server
};

#endif // MORALITYSERVER_H
