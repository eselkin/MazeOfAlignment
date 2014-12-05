#ifndef ALLITEMS_H
#define ALLITEMS_H
#include <vector>
#include <QMap>
#include "items.h"
#include "stats.h"
// we do have an items copy constructor to make copies of even pointers to items
struct allItems{
public :
    allItems();
    QMap<string, items*> itemlist;
};


#endif // ALLITEMS_H
