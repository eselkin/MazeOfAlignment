#ifndef PLAYER_H
#define PLAYER_H
#include "items.h"
#include "stats.h"
#include <QVector>

class player
{
public:
    player();
    void addStat(stats* newstat);
    void addItem(items* newitem);

private:
    QVector<items*> myitems;
    QVector<stats*> mystats;
};

#endif // PLAYER_H
