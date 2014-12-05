#ifndef RUNNABLEMAZE_H
#define RUNNABLEMAZE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QDebug>

class RunnableMaze : public QRunnable
{
public:
    RunnableMaze();

    int getSocketDesc();
    void setSocketDesc(int sd);

signals:

public slots:

protected:
    void run();

private:
    int SocketDescriptor;
};

#endif // RUNNABLEMAZE_H
