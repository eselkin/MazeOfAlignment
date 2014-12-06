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
    void commandToServer(qint32 ID, QByteArray packetcommand);

public slots:
    void readyRead();
    void disconnected();
    void commandToSocket(QByteArray thebytes);
    // should be encapsulated
    // packets of 512bytes or less beginning with the #bytes// so we'll know if whatever stripped of these bytes was complete
    // the client will then receive this data on it's connection until it has received enough bytes
    // Not sure what recourse if there weren't enough


private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // THREADOFMORALITY_H
