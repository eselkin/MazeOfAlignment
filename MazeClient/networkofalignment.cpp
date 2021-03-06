#include "networkofalignment.h"
#include <QNetworkSession>
#include <QStringList>
#include <QDebug>
#include <iostream>

using namespace std;

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
    // MAKE THE CONNECTION
    ct_socket->connectToHost(serverIPaddr, serverPort);

    if (!ct_socket->isOpen())
        qDebug() << "CONNECTION TO HOST NOT MADE";
    // DIRECTLY COPIED FROM ... AND I'm not 100% sure we need it
    //    http://qt-project.org/doc/qt-5/qtnetwork-fortuneclient-client-cpp.html

    // ACTUALLY WE DON'T NEED IT BUT IT SAVES THE NETWORK STATE.... SO MAYBE SOMEDAY WE CAN USE IT OR TWEAK IT

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
                QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        ct_session = new QNetworkSession(config, this);
        connect(ct_session, SIGNAL(opened()), this, SLOT(sessionOpened()));
        ct_session->open();
    }

    pollNetworkID();

}

void NetworkOfAlignment::pollNetworkID()
{
    ct_socket->waitForReadyRead(1000);
    QString commandString="SOCKETID::";
    int packetsize = commandString.size();
    QByteArray newBytes;
    newBytes.append(QString::number(packetsize));
    newBytes.append(tr("//"));
    newBytes.append(commandString);
    ct_socket->write(newBytes);
    ct_socket->write("\r\n");
    ct_socket->flush();
}

void NetworkOfAlignment::readyRead()
{
    /// READY READ ALLOWS US TO KNOW IF SOME DATA HAS COME IN ON THE SOCKET OF THIS THREAD, THEN EMITS
    /// A SIGNAL THAT GETS TAKEN UP BY A SLOT IN THE SERVER AND THEN REDISTRIBUTED AS NECCESSARY TO ALL
    /// THREADS

    QByteArray Data = ct_socket->readAll(); // read all when signaled that it is ready
    qDebug() << "Server sent: " << Data << endl;

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
    qDebug() << "READING FROM SERVER" <<endl;
    QString incomingcommand(packetcommand);
    if (!incomingcommand.contains("//") || !incomingcommand.contains("::"))
        return; // DONT DO ANYTHING WITH EMPTY LINES
    QStringList BytesCommand = incomingcommand.split("//",QString::SkipEmptyParts);
    qint16 bytesize(BytesCommand[0].toInt());
    //    if (BytesCommand[1].size() != bytesize)  // no it's not really bytes
    //        qDebug() << "incorrect packet size!"; // but do nothing... really how big are our packets? 20 bytes?
    QStringList CKeyVal = BytesCommand[1].split("::", QString::SkipEmptyParts);
    qDebug() << "0:" << CKeyVal[0]<< " 1:" << CKeyVal[1] <<endl;
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
        emit GameOver(QString::number(ct_socket->socketDescriptor()));
        // someone won, maybe even us so check it
        // advance to the next level if it exists...
        // If not, compare points? and end.
    } else if (CKeyVal[0] == "SOCKETID")
    {
        emit serverSocket(CKeyVal[1].toInt());
    } else if (CKeyVal[0] == "DAMAGE")
    {
        QStringList dmglist = CKeyVal[1].split("-", QString::SkipEmptyParts);
        int damage = dmglist[0].toInt();
        if (!dmglist[1].contains(","))
        {
            // just one to damage
            if (dmglist[1].toInt() != ct_socket->socketDescriptor())
                return;
            // damaging us
            emit gotDamage(damage);
            return;
        }
        QStringList players = dmglist[1].split(",", QString::SkipEmptyParts);
        for(int i = 0; i < players.size(); i++)
        {
            if (players[i].toInt() != ct_socket->socketDescriptor())
                continue;
            else
               emit gotDamage(damage);
        }
        return;
    }

}

void NetworkOfAlignment::moveToServer(int current_room)
{
    QString command = "LOCATION::";
    command.append(QString::number(current_room));
    int packetsize = command.size();
    command.prepend(tr("//"));
    command.prepend(QString::number(packetsize));
    QByteArray newCommand;
    qDebug() << "STRING:" << command <<endl;

    newCommand.append(command);
    ct_socket->write(newCommand);
    ct_socket->write("\r\n");
    ct_socket->flush();
}

bool NetworkOfAlignment::winToServer()
{
    QString command = "WINNING::";
    int packetsize = command.size();
    command.prepend(tr("//"));
    command.prepend(QString::number(packetsize));
    QByteArray newCommand;
    qDebug() << "STRING:" << command <<endl;

    newCommand.append(command);
    ct_socket->write(newCommand);
    ct_socket->write("\r\n");
    ct_socket->flush();
    return true;
}

bool NetworkOfAlignment::damageToServer(QString listfordmg)
{
    QString command = "DAMAGE::";
    command.append(listfordmg);
    int packetsize = command.size();
    command.prepend(tr("//"));
    command.prepend(QString::number(packetsize));
    QByteArray newCommand;
    qDebug() << "STRING: " << command << endl;
    newCommand.append(command);
    ct_socket->write(newCommand);
    ct_socket->write("\r\n");
    ct_socket->flush();
    return true;
}

int NetworkOfAlignment::getSocketID()
{
    return ct_socket->socketDescriptor();
}

void NetworkOfAlignment::displayError(QAbstractSocket::SocketError socketError)
{
    // blah, the one from the Qt Tutorials on Fortune network client, but no message boxes... that's silly here
    // http://qt-project.org/doc/qt-5/qtnetwork-fortuneclient-example.html
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
        qDebug() << ct_socket->errorString();
    }
}

void NetworkOfAlignment::SessionOpened()
{
    // DIRECTLY COPIED FROM ... AND I'm not 100% sure we need it
    //    http://qt-project.org/doc/qt-5/qtnetwork-fortuneclient-client-cpp.html
    // Save the used configuration
        QNetworkConfiguration config = ct_session->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = ct_session->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
}
