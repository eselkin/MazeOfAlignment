#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include "items.h"


typedef unsigned int uint;
class room
{
public:
    room();
    ~room();
    void addItem(items newitem);

private:
    vector<items*> avail_contents; // pointers so that when someone takes them, they can be transferred in just one memory space!
    vector<stats*> stat_alterations;
};

#endif // ROOM_H
