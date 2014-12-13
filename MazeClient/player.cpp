#include "player.h"
#include <QDebug>
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
    qDebug() << "PICKING UP ITEM" <<endl;
    myitems.push_back(newitem);

}

bool player::hasStat(QString stat, int val)
{
    return mystats[stat] > val;
}

bool player::hasItem(items *itemreq)
{
    qDebug() << "HERE IN HAS ITEM!" <<endl;
    bool hasit = false;
    int itemsize = myitems.size();
    for (int i = 0; i < itemsize; i++)
    {
        qDebug() << " HAVE:" << myitems[i]->getId() << " LOOKING FOR: " << itemreq->getId() << endl;
        if (myitems[i]->getId() == itemreq->getId())
            return true;
    }
    return false;
}
