#include "threadofmorality.h"
#include <QDebug>

ThreadOfMorality::ThreadOfMorality(int ID, QObject *parent) :
    QThread(parent), socketDescriptor(ID)
{
}

void ThreadOfMorality::run()
{
    qDebug() << "Thread started" << endl;
    socket = new QTcpSocket;

    if (!socket->setSocketDescriptor(getSocketDescriptor()))
    {
        // error out
        emit error(socket->error());
        return;
    }

    // DirectConnection is Threaded, but isn't this dangerous for overloading the system
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << getSocketDescriptor() << " client connected.";

    exec(); // execute and hold in memory
}

void ThreadOfMorality::readyRead()
{
    /// READY READ ALLOWS US TO KNOW IF SOME DATA HAS COME IN ON THE SOCKET OF THIS THREAD, THEN EMITS
    /// A SIGNAL THAT GETS TAKEN UP BY A SLOT IN THE SERVER AND THEN REDISTRIBUTED AS NECCESSARY TO ALL
    /// THREADS
    qDebug() << "READING DATA FROM SOCKET..." << endl;
    QByteArray Data = socket->readAll(); // read all when signaled that it is ready

    qDebug() << "client with desc: " << socketDescriptor << " sent: " << Data << endl;

    // BREAK UP THE CLIENT REQUEST HERE
    //
    // HEADER KEY ::VALUE               // Meaning
    //    LOCATION::1,2                 // Level, Room... thus everyone should be on the same level
    //     WINNING::                    // SocketDescriptor just won the level
    //       SCORE::                    // We can have it "display" everyones score

    //....
    // This will then signal the server (parent) and that will then in turn signal all the threads.
    //....
    emit commandToServer(socket->socketDescriptor(), Data);
}

void ThreadOfMorality::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    emit socketdisconnect(socketDescriptor); // delete player info from data to be broadcast and tracked
    exit(0);
}

void ThreadOfMorality::commandToSocket(QByteArray thebytes)
{
    qDebug() << "BYTE:" << thebytes <<endl;
    socket->write(thebytes);
    socket->write("\r\n"); // terminate the line because we will be using readLine on the socket for the client.
}

int ThreadOfMorality::getSocketDescriptor() const
{
    return socketDescriptor;
}

void ThreadOfMorality::setSocketDescriptor(const int& value)
{
    socketDescriptor = value;
}

