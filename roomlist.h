#ifndef ROOMLIST_H
#define ROOMLIST_H
#include "allItems.h"
#include "room.h"
// make a list of rooms here
struct roomlist
{
    roomlist();
    room *therooms[7][64];
};

#endif // ROOMLIST_H


roomlist::roomlist()
{
    for (uint i = 0; i < 7; i++)
    {
        for (uint j = 0; j < 64; j++)
            therooms[i][j] = NULL;
    }
}
