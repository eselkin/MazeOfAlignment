#ifndef WEIGHTS_H
#define WEIGHTS_H
#include "items.h"
#include "stats.h"
#include <vector>
#include <string>
using namespace std;

class weights
{
public:
    weights();
    void addItem( string item_name , string identifier);
    void addStat( string stat_name , int value );
    int isDoor() const;
    void setDoor(int type); // 0 = nothing, 1 = wall, 2 = unlocked door, 3 = locked door

private:
    int my_door;
    vector< items* > itemsReq;
    vector< stats* > statsReq; // Required to enter
};

#endif // WEIGHTS_H
