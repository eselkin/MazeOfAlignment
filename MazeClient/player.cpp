#include "player.h"

player::player()
{
}

void player::addStat(pair<pair<QString, int>, pair<QString, int> > newstat)
{
    if (newstat.first.first != "")
        addStat(newstat.first.first, newstat.first.second);
    if (newstat.second.first != "")
        addStat(newstat.second.first, newstat.second.second);
}

void player::addStat(QString newstat, int newqty)
{
    mystats.insert(newstat, newqty);
}

void player::addItem(items *newitem)
{
    myitems.push_back(newitem);

}
