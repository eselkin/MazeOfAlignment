#include "items.h"

items::items(const string& name, const string& identifier)
{
    itemname = name;
    item_id = identifier;
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

string items::getName() const
{
    return itemname;
}

string items::getId() const
{
    return item_id;
}

void items::copy(const items &other)
{
    itemname = other.getName();
    item_id = other.getId();
}

void items::nukem()
{

}
