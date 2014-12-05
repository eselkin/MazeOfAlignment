#ifndef THREADOFMORALITY_H
#define THREADOFMORALITY_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

typedef qint64* qintptr;

class ThreadOfMorality : public QThread
{
    Q_OBJECT
public:
    explicit ThreadOfMorality(qintptr ID, QObject *parent = 0);
    void run();

    qintptr getSocketDescriptor() const;
    void setSocketDescriptor(const qintptr &value);

signals:
    void error(QTcpSocket::SocketError e);

public slots:
    void readyRead();
    void disconnected();
    void commandSocket(QByteArray thebytes);
    // should be encoded
    // packets of 512bytes or less beginning with the #bytes// so we'll know if whatever stripped of these bytes was complete
    // the client will then receive this data on it's connection until it has received enough bytes and then packages that
    // Then
private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // THREADOFMORALITY_H
