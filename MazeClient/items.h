#ifndef ITEMS_H
#define ITEMS_H
#include <QString>

using namespace std;
typedef pair<QString, int> mQPair;

class items {
public:
    items(const QString &name, const QString& identifier, QString stat_i= "", int val_i = 0,QString stat_ii = "", int val_ii = 0);
    items(const QString &name, const QString& identifier, pair<mQPair,mQPair> statpair);
    items(const items &other);
    items& operator=(const items &other);
    ~items();
    QString getName() const;
    QString getId() const;
    pair<mQPair,mQPair> getStats() const;

private:
    void copy(const items &other);
    void nukem();
    QString itemname;
    QString item_id;
    pair< mQPair, mQPair > stat_add;
};

#endif // ITEMS_H
