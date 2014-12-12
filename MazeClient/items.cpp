#include "items.h"

items::items(const QString& name, const QString& identifier, pair<pair<QString, int>,pair<QString, int> > newstat)
{
    itemname = name;
    item_id = identifier;
    stat_add = newstat;
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

void items::copy(const items &other)
{
    itemname = other.getName();
    item_id = other.getId();
    stat_add = other.getStats();
}

void items::nukem()
{

}
