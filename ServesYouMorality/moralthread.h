#ifndef MORALTHREAD_H
#define MORALTHREAD_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
///
///
/// The ThreadOfMorality class
/// This class is meant for use by the MoralityServer class. Each connection
/// is places into a thread of this class and a run() is called when start()
/// is called. In run() the socket is created to handle communication with a
/// client. The server can broadcast messages to its threads with signal and
/// slot mechanisms. The commandToServer sends data to the server through it
/// and the server responds with to us through a call to the commandToSocket
/// slot. The server's response is then transferred to the conncected client
/// and the procedure ends but connection is maintained until destroyed by a
/// disconnection of the client or server.
///
/// Packets between the client and the server are encapsulated with a method
/// that is described in the readyRead() function.
///


class MoralThread : public QObject
{
    Q_OBJECT
public:
    explicit MoralThread(int ID, QObject *parent = 0);
    ~MoralThread();
    int getSocketDescriptor() const;
    void setSocketDescriptor(const int &value);

signals:
    void error(QTcpSocket::SocketError e);
    void socketdisconnect(int SD); // issue disconnect so server can catch it and remove player info
    void commandToServer(int ID, MoralThread *theThread, QByteArray packetcommand);

public slots:
    void readyRead();
    void disconnected();
    void commandToSocket(QByteArray thebytes);

private:
    QTcpSocket *socket;
    int socketDescriptor;
};

#endif // MORALTHREAD_H
