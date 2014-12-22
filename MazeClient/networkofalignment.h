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
    explicit NetworkOfAlignment(QString serverIPaddr, int serverPort, QObject *parent = 0);

signals:
    void commandToThread(QByteArray packetcommand);
    void LocationsChanged(QStringList playerlocations);
    void GameOver(QString Player);
    void gotDamage(int);

public slots:
    void readyRead();
    void disconnected();
    void SessionOpened();
    void commandToClient(QByteArray packetcommand);
    void moveToServer(int current_room);
    bool winToServer();
    bool damageToServer(QString listfordmg);
    void pollNetworkID();
    int getSocketID();


private slots:
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QString ct_name;
    QList<QHostAddress> ct_IPaddrs;
    QTcpSocket *ct_socket;
    QNetworkSession *ct_session;
    QString s_address;
    int s_port;
};

#endif // NETWORKOFALIGNMENT_H
