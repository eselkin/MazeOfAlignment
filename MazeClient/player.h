#ifndef PLAYER_H
#define PLAYER_H
#include "items.h"
#include "bst.h"
#include <QVector>
#include <QString>

class player
{
public:
    player();
    void addStat(QString newstat, int newqty);
    void addStat(pair<pair <QString, int>, pair <QString, int> > newstat);
    void addItem(items* newitem);

private:
    QVector<items*> myitems;
    bst<QString> mystats;
};

#endif // PLAYER_H
