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



items::items(const string& name, const string& identifier)
{
    itemname = name;
    item_id = identifier;
}

items::items(const items &other)
{
    copy (other);
}

items &items::operator=(const items &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

string items::getName() const
{
    return itemname;
}

string items::getId() const
{
    return item_id;
}

void items::copy(const items &other)
{
    itemname = other.getName();
    item_id = other.getId();
}

void items::nukem()
{

}
#endif // ITEMS_H
