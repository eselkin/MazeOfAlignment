#include "room.h"

room::room()
{
}

room::room(const room &other)
{
    copy(other);
}

room &room::operator=(const room &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

room::~room()
{
    uint sizeofroom = avail_contents.size();
    uint numattributes = stat_alterations.size();
    for (uint i =0; i < sizeofroom; i++)
        delete avail_contents[i];
    for (uint i =0; i < numattributes; i++)
        delete stat_alterations[i];
    avail_contents.clear();
    stat_alterations.clear();
}

vector<stats *> room::getStats() const
{
    return stat_alterations;
}

vector<items *> room::getItems() const
{
    return avail_contents;
}

void room::addItem(items newitem)
{
    avail_contents.push_back(new items(newitem));
}

void room::copy(const room &other)
{
    uint other_size = other.getItems().size();
    for (uint i = 0; i < other_size; i++)
        avail_contents.push_back(new items(*other.getItems()[i]));
    other_size = other.getStats().size();
    for (uint i = 0; i < other_size; i++)
        stat_alterations.push_back(new stats(*other.getStats()[i]));
}

void room::nukem()
{

}
