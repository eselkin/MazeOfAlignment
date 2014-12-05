#ifndef MORALITYSERVER_H
#define MORALITYSERVER_H

#include <QTcpServer>
#include <QThreadPool>
#include <QDebug>
#include "runnablemaze.h"
class MoralityServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MoralityServer(QObject *parent = 0);
    void StartServer();

signals:

protected:
    void incomingConnection(int handle);

public slots:

private:
    QThreadPool *PoolOfMorality;
};

#endif // MORALITYSERVER_H
