#ifndef NETWORKOFALIGNMENT_H
#define NETWORKOFALIGNMENT_H

#include <QObject>
#include <QtNetwork>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>

// NETWORKING CLIENT
class NetworkOfAlignment : public QObject
{
    Q_OBJECT
public:
    explicit NetworkOfAlignment(QString serverIPaddr, QObject *parent = 0);

signals:
    void commandToThread(QByteArray packetcommand);
    void LocationsChanged(QStringList playerlocations);

public slots:
    void readyRead();
    void disconnected();
    void commandToClient(QByteArray packetcommand);

private:
    QString ct_name;
    QList<QHostAddress> ct_IPaddrs;
    QTcpSocket *ct_socket;
};

#endif // NETWORKOFALIGNMENT_H
