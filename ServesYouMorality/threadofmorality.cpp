#include "threadofmorality.h"

ThreadOfMorality::ThreadOfMorality(qintptr ID, QObject *parent) :
    QThread(parent)
{
    setSocketDescriptor(ID);
}

void ThreadOfMorality::run()
{
    qDebug() << "Thread started" << endl;
    socket = new QTcpSocket();
    if (!socket->socketDescriptor(getSocketDescriptor()))
    {
        // error out
        emit error(socket->error());
        return;
    }

    // DirectConnection is Threaded, but isn't this dangerous for overloading the system
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(), this, SLOT());

    qDebug() << getSocketDescriptor() << " client connected.";

    exec(); // execute and hold in memory
}

void ThreadOfMorality::readyRead()
{
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
    // RESPOND TO THE CLIENT REQUEST HERE!
    // Response to the client would be more difficult and would have to have repeating keys for which we can use regular expressions to split
    //    LOCATION::ID1-1,ID2-4,ID3-19 // {socket descriptor that your computer would turn into player 0, 1, 2, ... n players
    //    WINNING ::ID                 // Which socket descriptor won
    //    SCORE   ::ID1-900,ID2-100000 // etc.
}

void ThreadOfMorality::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}

qintptr ThreadOfMorality::getSocketDescriptor() const
{
    return socketDescriptor;
}

void ThreadOfMorality::setSocketDescriptor(const qintptr &value)
{
    socketDescriptor = value;
}

