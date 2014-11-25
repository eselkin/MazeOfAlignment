#ifndef ITEMS_H
#define ITEMS_H
#include <string>

using namespace std;

class items {
public:
    items(const string &name, const string& identifier);
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
};

#endif // ITEMS_H
