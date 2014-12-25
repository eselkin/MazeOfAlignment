#include "moralthread.h"

MoralThread::MoralThread(int ID, QObject *parent) :
    QObject(parent) , socketDescriptor(ID)
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
}

MoralThread::~MoralThread()
{

}

void MoralThread::readyRead()
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
    emit commandToServer(socketDescriptor, this, Data);
}


void MoralThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    emit socketdisconnect(socketDescriptor); // delete player info from data to be broadcast and tracked
    deleteLater();
}

void MoralThread::commandToSocket(QByteArray thebytes)
{
    qDebug() << "ARE WE HERE!" << endl;
    if (thebytes.contains("SOCKETID"))
    {
        QString temp = QString(thebytes);
        QStringList templist = temp.split("::",QString::SkipEmptyParts);
        temp = templist[1];
        if (temp.toInt() == socket->socketDescriptor())
        {
            socket->write(thebytes);
            socket->write("\r\n"); // terminate the line because we will be using readLine on the socket for the client.
            socket->flush();
            qDebug() << "BYTE:" << thebytes <<endl;
        }
    }
    else
    {
        socket->write(thebytes);
        socket->write("\r\n"); // terminate the line because we will be using readLine on the socket for the client.
        socket->flush();
        qDebug() << "BYTE:" << thebytes <<endl;
    }
}

int MoralThread::getSocketDescriptor() const
{
    return socketDescriptor;
}

void MoralThread::setSocketDescriptor(const int& value)
{
    socketDescriptor = value;
}


