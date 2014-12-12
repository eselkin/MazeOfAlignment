#include "player.h"

player::player()
{
}

void player::addStat(pair<mQPair, mQPair> newstat)
{
    if (newstat.first.first != "")
        addStat(newstat.first.first, newstat.first.second);
    if (newstat.second.first != "")
        addStat(newstat.second.first, newstat.second.second);
}

void player::addStat(QString newstat, int newqty)
{
    mystats.insert(&newstat, newqty);
}

void player::addItem(items *newitem)
{
    myitems.push_back(newitem);

}

bool player::hasStat(QString stat, int val)
{
    mystats.find
}

bool player::hasItem(items *itemreq)
{

}
