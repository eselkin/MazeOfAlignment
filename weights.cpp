#include "weights.h"

weights::weights()
{
}

// we can add an unlimited number of item or stat requirements to the room's entrance "fee"
void weights::addItem(string item_name, string identifier)
{
    itemsReq.push_back(new items(item_name, identifier));
}

void weights::addStat(string stat_name, int value)
{
    statsReq.push_back(new stats(stat_name, value));
}
