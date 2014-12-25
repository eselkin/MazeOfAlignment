#ifndef MORALTHREAD_H
#define MORALTHREAD_H

#include <QObject>

class MoralThread : public QObject
{
    Q_OBJECT
public:
    explicit MoralThread(QObject *parent = 0);
    ~MoralThread();

signals:

public slots:
};

#endif // MORALTHREAD_H
