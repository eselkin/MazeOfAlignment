#include "items.h"

items::items(const QString& name, const QString& identifier, QString stat_i, int val_i, QString stat_ii, int val_ii)
{
    itemname = name;
    item_id = identifier;
    stat_add = make_pair(make_pair(stat_i,val_i),make_pair(stat_ii,val_ii));
}

items::items(const QString &name, const QString &identifier, pair<mQPair, mQPair> statpair)
{
    itemname = name;
    item_id = identifier;
    stat_add = statpair;
}

items::items(const items &other)
{
    copy (other);
}

items &items::operator=(const items &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

items::~items()
{

}

QString items::getName() const
{
    return itemname;
}

QString items::getId() const
{
    return item_id;
}

pair<mQPair, mQPair> items::getStats() const
{
    return stat_add;
}

void items::copy(const items &other)
{
    itemname = other.getName();
    item_id = other.getId();
    stat_add = other.getStats();
}

void items::nukem()
{

}
