#ifndef THREADOFMORALITY_H
#define THREADOFMORALITY_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

#ifdef __linux__
typedef qint32* qintptr;
#endif

///
/// CHANGE THE ABOVE TYPEDEF TO ADD #ifdef __APPLE__
/// and the same next two lines if you get an error building
/// on Apple... Windows Qt has a typedef for qintptr already
/// in QtGlobal
///


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

class ThreadOfMorality : public QThread
{
    Q_OBJECT
public:
    explicit ThreadOfMorality(qint32 ID, QObject *parent = 0);
    void run();

    qintptr getSocketDescriptor() const;
    void setSocketDescriptor(const qintptr &value);

signals:
    void error(QTcpSocket::SocketError e);
    void socketdisconnect(qint32 SD); // issue disconnect so server can catch it and remove player info
    void commandToServer(qint32 ID, QByteArray packetcommand);

public slots:
    void readyRead();
    void disconnected();
    void commandToSocket(QByteArray thebytes);

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // THREADOFMORALITY_H
