#ifndef NETWORKOFALIGNMENT_H
#define NETWORKOFALIGNMENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>


// NETWORKING CLIENT
class NetworkOfAlignment : public QObject
{
    Q_OBJECT
public:
    explicit NetworkOfAlignment(QString serverIPaddr, QObject *parent = 0);

signals:

public slots:
    QString ct_name;
    QList<QHostAddress> ct_IPaddrs;
    QTcpSocket *ct_socket;
};

#endif // NETWORKOFALIGNMENT_H
