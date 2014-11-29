#include "room.h"

room::room()
{
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

void room::addItem(items newitem)
{
    avail_contents.push_back(new items(newitem));
}
