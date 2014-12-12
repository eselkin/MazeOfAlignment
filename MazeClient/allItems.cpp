#include "allItems.h"


allItems::allItems()
{
    itemlist.insert("key_blue", new items("Blue Key",   "key_blue"));
    itemlist.insert("key_black", new items("Black Key",   "key_black"));
    itemlist.insert("key_red", new items("Red Key",   "key_red"));
    itemlist.insert("key_gold", new items("Gold Key",   "key_gold"));
    itemlist.insert("key_silver", new items("Silver Key",   "key_silver"));
    itemlist.insert("weapon_spear", new items("Spear",   "weapon_spear", "damage", 10)));
    itemlist.insert("orb_win", new items("The Orb",   "orb_win"));
}

