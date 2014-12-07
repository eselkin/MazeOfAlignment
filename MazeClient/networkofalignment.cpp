#include "networkofalignment.h"

NetworkOfAlignment::NetworkOfAlignment(QString serverIPaddr, QObject *parent) :
    QObject(parent)
{
    // Create the socket
    ct_socket  = new QTcpSocket(this); // we connect the socket to this because it is not a thread, but an instance of an object
    // set up connection information
    ct_name    = QHostInfo::localHostName();
    ct_IPaddrs = QNetworkInterface::allAddresses();
    // when we receive a readyRead() from the thread of the server, we read it as a command coming from the server
    connect( ct_socket, SIGNAL(readyRead()), this, SLOT(readyRead()) );


}

void NetworkOfAlignment::readyRead()
{

}

void NetworkOfAlignment::disconnected()
{

}

void NetworkOfAlignment::commandToClient(QByteArray thebytes)
{

}
