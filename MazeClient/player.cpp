#include "player.h"
#include <QDebug>
player::player()
{
}

void player::addStat(pair<mQPair, mQPair> newstat)
{
    if (newstat.first.first != "")
    {
        qDebug() << "newstat value 1: " << newstat.first.second;
        addStat(newstat.first.first, newstat.first.second);
    }
    if (newstat.second.first != "")
    {
        qDebug() << "newstat value 2: " << newstat.second.second;
        addStat(newstat.second.first, newstat.second.second);
    }
}

void player::addStat(QString newstat, int newqty)
{
    mystats.insert(&newstat, newqty);
}

void player::addItem(items *newitem)
{
    addStat(newitem->getStats());
    myitems.push_back(newitem);
}

void player::dropItem(items *remitem)
{
    QVector<items*>::iterator vIT;
    for (vIT=myitems.begin(); vIT != myitems.end(); vIT++)
        if ((*vIT)->getId() == remitem->getId())
            myitems.erase(vIT);
}


// No dropping stats, just adding negative quantities

bool player::hasStat(QString stat, int val)
{
    qDebug() << "MYSTAT: " << stat << " is: " << mystats[stat] << " AND REQ IS: " << val;
    return mystats[stat] > val;
}

bool player::hasItem(items *itemreq)
{
    int itemsize = myitems.size();
    for (int i = 0; i < itemsize; i++)
        if (myitems[i]->getId() == itemreq->getId())
            return true;
    return false;
}
