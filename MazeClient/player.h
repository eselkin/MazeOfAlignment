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
    int  getStat(QString stat);
    bool hasItem(items* itemreq);
    bool dropItem(items *remitem);
    bool doDamage();
    QVector<items*>& getItems();

public slots:
    bool TakeDamage(int damage);
    bool resetstats();

signals:
    void DamageOther(int);
    void rebirth();

private:
    QVector<items*> myitems;
    bst<QString> mystats;

};

#endif // PLAYER_H
