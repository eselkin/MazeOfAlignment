#include "networkofalignment.h"
#include <QStringList>
#include <QDebug>

NetworkOfAlignment::NetworkOfAlignment(QString serverIPaddr, int serverPort, QObject *parent) :
    QObject(parent), ct_session(0)
{
    // Create the socket
    ct_socket  = new QTcpSocket(this); // we connect the socket to this because it is not a thread, but an instance of an object
    // set up connection information
    ct_name    = QHostInfo::localHostName();
    ct_IPaddrs = QNetworkInterface::allAddresses();
    // when we receive a readyRead() from the thread of the server, we read it as a command coming from the server
    connect( ct_socket, SIGNAL(readyRead()), this, SLOT( readyRead()) );
    connect( ct_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    s_address = serverIPaddr;
    s_port = serverPort;
    // MAKE THE CONNECTION
    ct_socket->connectToHost(s_address, s_port);

}

void NetworkOfAlignment::readyRead()
{
    /// READY READ ALLOWS US TO KNOW IF SOME DATA HAS COME IN ON THE SOCKET OF THIS THREAD, THEN EMITS
    /// A SIGNAL THAT GETS TAKEN UP BY A SLOT IN THE SERVER AND THEN REDISTRIBUTED AS NECCESSARY TO ALL
    /// THREADS

    QByteArray Data = ct_socket->readLine(10000); // read all when signaled that it is ready
    qDebug() << "Severe sent: " << Data << endl;

    // BREAK UP THE CLIENT REQUEST HERE
    //
    // HEADER KEY ::VALUE               // Meaning
    //    LOCATION::1,2                 // Level, Room... thus everyone should be on the same level
    //     WINNING::                    // SocketDescriptor just won the level
    //       SCORE::                    // We can have it "display" everyones score

    //....
    // This will then signal the server (parent) and that will then in turn signal all the threads.
    //....
    commandToClient(Data);
}

void NetworkOfAlignment::disconnected()
{

}

void NetworkOfAlignment::commandToClient(QByteArray packetcommand)
{
    QString incomingcommand(packetcommand);
    if (!incomingcommand.contains("//") || !incomingcommand.contains("::"))
        return; // DONT DO ANYTHING WITH EMPTY LINES
    QStringList BytesCommand = incomingcommand.split("//",QString::SkipEmptyParts);
    qint16 bytesize(BytesCommand[0].toInt());
    if (BytesCommand[1].size() != bytesize)  // no it's not really bytes
        qDebug() << "incorrect packet size!"; // but do nothing... really how big are our packets? 20 bytes?
    QStringList CKeyVal = BytesCommand[1].split("::", QString::SkipEmptyParts);
    if (CKeyVal[0] == "LOCATION")
    {
        QStringList PlayerLocations;
        if (CKeyVal[1].contains(","))
            PlayerLocations = CKeyVal[1].split(",", QString::SkipEmptyParts);
        else
            PlayerLocations << CKeyVal[1];
        // now we have a list of locations for each player
        emit LocationsChanged(PlayerLocations);
    } else if (CKeyVal[0] == "WINNING")
    {
        // someone won, maybe even us so check it
        // advance to the next level if it exists...
        // If not, compare points? and end.
    }
}

void NetworkOfAlignment::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "SERVER NOT FOUND AT ADDRESS: " << s_address << " AND PORT: " << s_port <<endl;
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "SERVER NOT FOUND AT ADDRESS: " << s_address << " AND PORT: " << s_port <<endl;
        break;
    default:
        qDebug << tcpSocket->errorString();
    }
}
