#include "roomlist.h"

roomlist::roomlist()
{
    for (uint i = 0; i < 7; i++)
    {
        for (uint j = 0; j < 64; j++)
            rooms[i][j] = new room();
    }

    rooms[0][9]->addItem(listofitems.itemlist["key_black"]);
    rooms[1][49]->addItem(listofitems.itemlist["orb_win"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_gold"]);
    rooms[1][17]->addItem(listofitems.itemlist["orb_win"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_black"]);
    rooms[1][17]->addItem(listofitems.itemlist["weapon_spear"]);
}

