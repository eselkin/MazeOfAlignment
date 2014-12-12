#ifndef PLAYER_H
#define PLAYER_H
#include "items.h"
#include "bst.h"
#include <QVector>
#include <QString>

using namespace std;
typedef pair<QString, int> mQPair;

class player
{
public:
    player();
    void addStat(QString newstat, int newqty);
    void addStat(pair<mQPair,mQPair> newstat);
    void addItem(items* newitem);
    bool hasStat(QString stat, int val);
    bool hasItem(items* itemreq);
private:
    QVector<items*> myitems;
    bst<QString> mystats;
};

#endif // PLAYER_H
