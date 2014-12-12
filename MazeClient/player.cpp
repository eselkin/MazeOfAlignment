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
    return mystats[stat] > val;
}

bool player::hasItem(items *itemreq)
{
    bool hasit = false;
    int itemsize = myitems.size();
    for (int i = 0; i < itemsize; i++)
    {
        (myitems[i] == itemreq) && (hasit == false) && (hasit = true);
    }
    return hasit;
}
