#ifndef WEIGHTS_H
#define WEIGHTS_H
#include "items.h"
#include <vector>
#include <QString>

using namespace std;
typedef pair<QString, int> mQPair;


class weights
{
public:
    weights();
    void addItem(QString item_name , QString identifier, pair<mQPair,mQPair> statpair = make_pair(make_pair("",0), make_pair("",0)));
    void addStat(QString stat_name, int value, QString stat_two, int value_two);
    void addStat(pair<mQPair, mQPair> );
    vector<pair<mQPair, mQPair> > &getStats();
    vector< items* >& getItems();

    int isDoor() const;
    void setDoor(int type); // 0 = nothing, 1 = wall, 2 = unlocked door, 3 = locked door

private:
    int my_door;
    vector< items* > itemsReq;
    vector< pair<mQPair, mQPair> > statsReq; // Required to enter
};

#endif // WEIGHTS_H
