#include "runnablemaze.h"

RunnableMaze::RunnableMaze(QObject *parent)
{
}

int RunnableMaze::getSocketDesc()
{
    return SocketDescriptor;
}

void RunnableMaze::setSocketDesc(int sd)
{
    SocketDescriptor = sd;
}

void RunnableMaze::run()
{
    if (!SocketDescriptor) return;
    // quick exit

    QTcpSocket socket;
    socket.setSocketDescriptor(SocketDescriptor);


    // Where we interact with the socket
    socket.write("Connected to runnable maze server");
    socket.flush();
    socket.waitForBytesWritten();
    socket.close();

}
