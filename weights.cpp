#include "weights.h"
#include <QDebug>

weights::weights()
{
    my_door = 0;
}

// we can add an unlimited number of item or stat requirements to the room's entrance "fee"
void weights::addItem(string item_name, string identifier)
{
    itemsReq.push_back(new items(item_name, identifier));
}

void weights::addStat(string stat_name, int value)
{
    statsReq.push_back(new stats(stat_name, value));
}

int weights::isDoor() const
{
    return my_door;
}

void weights::setDoor(int type)
{
    my_door = type;
}
