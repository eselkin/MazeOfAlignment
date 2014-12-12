#ifndef ALLITEMS_H
#define ALLITEMS_H
#include <vector>
#include <QMap>
#include "items.h"
#include <QString>
// we do have an items copy constructor to make copies of even pointers to items
struct allItems{
public :
    allItems();
    QMap<QString, items*> itemlist;
};


#endif // ALLITEMS_H
