#ifndef PLAYER_H
#define PLAYER_H
#include "items.h"
#include "bst.h"
#include <QVector>
#include <QObject>
#include <QString>

using namespace std;
typedef pair<QString, int> mQPair;

class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent = 0);
    void addStat(QString newstat, int newqty);
    void addStat(pair<mQPair,mQPair> newstat);
    void addItem(items* newitem);
    bool hasStat(QString stat, int val);
    bool hasItem(items* itemreq);
    bool dropItem(items *remitem);
    QVector<items*>& getItems();

public slots:
    void TakeDamage(int damage);

signals:
    void DamageOther(int);

private:
    QVector<items*> myitems;
    bst<QString> mystats;

};

#endif // PLAYER_H
