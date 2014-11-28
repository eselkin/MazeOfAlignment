#include "room.h"

room::room()
{
}

void room::addItem(items newitem)
{
    avail_contents.push_back(new items(newitem));
}
