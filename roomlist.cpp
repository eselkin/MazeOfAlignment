#include "roomlist.h"

roomlist::roomlist()
{
    for (uint i = 0; i < 7; i++)
    {
        for (uint j = 0; j < 64; j++)
            rooms[i][j] = NULL;
    }
    rooms[0][9]->addItem(*listofitems.itemlist["key_black"]);
    rooms[1][17]->addItem(*listofitems.itemlist["key_gold"]);
}

