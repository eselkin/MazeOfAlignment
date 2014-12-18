#include "player.h"
#include <QDebug>

player::player(QObject *parent):
    QObject(parent)
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
    addStat(newitem->getStats());
    myitems.push_back(newitem);
}

bool player::dropItem(items *remitem)
{
    for (int i=0; i < myitems.size(); i++)
        if (myitems[i]->getId() == remitem->getId()) // drop the first item with that ID
            myitems.remove(i);
    return true;
}

QVector<items *> &player::getItems()
{
    return myitems;
}

void player::TakeDamage(int damage)
{
    QString HLTH=tr("Health");
    mystats.insert(&HLTH, -1*damage);
}


// No dropping stats, just adding negative quantities

bool player::hasStat(QString stat, int val)
{
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
