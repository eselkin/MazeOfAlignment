#ifndef ITEMS_H
#define ITEMS_H
#include <QString>

using namespace std;

class items {
public:
    items(const QString &name, const QString& identifier, pair<pair<QString, int>, pair<QString, int> > newstat);
    items(const items &other);
    items& operator=(const items &other);
    ~items();
    QString getName() const;
    QString getId() const;
    pair<pair<QString, int>, pair<QString, int> > getStats() const;

private:
    void copy(const items &other);
    void nukem();
    QString itemname;
    QString item_id;
    pair<pair<QString, int>, pair<QString, int> > stat_add;
};

#endif // ITEMS_H
