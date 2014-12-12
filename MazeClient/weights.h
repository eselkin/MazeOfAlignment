#ifndef WEIGHTS_H
#define WEIGHTS_H
#include "items.h"
#include <vector>
#include <QString>
using namespace std;

class weights
{
public:
    weights();
    void addItem(QString item_name , QString identifier, pair<pair<QString, int>, pair<QString, int> > statpair = pair<pair<QString, int>, pair<QString, int> >(pair<QString,int>("",0), pair<QString, int>("",0)));
    void addStat(QString stat_name, int value, QString stat_two, int value_two);
    void addStat(pair<pair<QString, int>, pair<QString, int> > );
    int isDoor() const;
    void setDoor(int type); // 0 = nothing, 1 = wall, 2 = unlocked door, 3 = locked door

private:
    int my_door;
    vector< items* > itemsReq;
    vector< pair<pair<QString, int>, pair<QString, int> > > statsReq; // Required to enter
};

#endif // WEIGHTS_H
