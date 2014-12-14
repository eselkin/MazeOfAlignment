#include "allItems.h"


allItems::allItems()
{
    itemlist.insert("key_blue",     new items("Blue Key",   "key_blue",     "Good",    5,  "Neutral",  5));
    itemlist.insert("key_black",    new items("Black Key",  "key_black",    "Good",    10, "Evil",     10));
    itemlist.insert("key_red",      new items("Red Key",    "key_red",      "Neutral", 10, "Lawful",   25));
    itemlist.insert("key_gold",     new items("Gold Key",   "key_gold",     "Good",    10, "Lawful",   10));
    itemlist.insert("key_silver",   new items("Silver Key", "key_silver",   "Lawful",  10, "Neutral",  5));
    itemlist.insert("weapon_spear", new items("Spear",      "weapon_spear", "Damage",  10, "Strength", 5));
    itemlist.insert("weapon_axe",   new items("Axe",        "weapon_axe",   "Damage",  15, "Strength", 10));
    itemlist.insert("orb_win",      new items("The Orb",    "orb_win",      "Good",    20, "Winning",  100));
}

