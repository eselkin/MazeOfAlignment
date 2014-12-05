#ifndef RUNNABLEMAZE_H
#define RUNNABLEMAZE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QDebug>

class RunnableMaze : public QRunnable
{
    Q_OBJECT
public:
    explicit RunnableMaze(QObject *parent = 0);
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
