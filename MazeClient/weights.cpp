#include "weights.h"
#include <QDebug>
#include <QString>

weights::weights()
{
    my_door = 0;
}

// we can add an unlimited number of item or stat requirements to the room's entrance "fee"
void weights::addItem(QString item_name, QString identifier, pair<mQPair, mQPair> statpair)
{
    itemsReq.push_back(new items(item_name, identifier, statpair));
}

void weights::addStat(pair<mQPair, mQPair> statpair)
{
    statsReq.push_back(statpair);
}

vector<pair<mQPair, mQPair>> &weights::getStats()
{
    return statsReq;
}

vector<items *> &weights::getItems()
{
    return itemsReq;
}

void weights::addStat(QString stat_name, int value, QString stat_two, int value_two)
{
    addStat(make_pair(make_pair(stat_name, value), make_pair(stat_two, value_two)));
}

int weights::isDoor() const
{
    return my_door;
}

void weights::setDoor(int type)
{
    my_door = type;
}
