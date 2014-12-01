#ifndef ROOMLIST_H
#define ROOMLIST_H

#include "allItems.h"
#include "room.h"
// make a list of rooms here
struct roomlist
{
    roomlist();
    allItems listofitems;
    room *rooms[7][64];
};

#endif // ROOMLIST_H
