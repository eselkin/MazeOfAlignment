#include "player.h"

player::player()
{
}

void player::addStat(stats *newstat)
{
    mystats.push_back(newstat);
}

void player::addItem(items *newitem)
{
    myitems.push_back(newitem);

}
