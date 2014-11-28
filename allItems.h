#ifndef ALLITEMS_H
#define ALLITEMS_H
#include "items.h"
#include "stats.h"
// we do have an items copy constructor to make copies of even pointers to items
items key_blue = items("Blue Key", "key_blue");
items key_red = items("Red Key", "key_red");
items key_black = items("Black Key", "key_black");
items key_silver = items("Silver Key", "key_silver");
items spear = items("Spear", "weapon_spear", stats("damage",10));

#endif // ALLITEMS_H
