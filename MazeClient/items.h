#ifndef ITEMS_H
#define ITEMS_H
#include <string>
#include "stats.h"

using namespace std;

class items {
public:
    items(const string &name, const string& identifier, stats stat_add = stats());
    items(const items &other);
    items& operator=(const items &other);
    ~items();
    string getName() const;
    string getId() const;

private:
    void copy(const items &other);
    void nukem();
    string itemname;
    string item_id;
    stats stat_add;
};

#endif // ITEMS_H
