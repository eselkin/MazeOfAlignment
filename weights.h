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
private:
    vector< items* > itemsReq;
    vector< stats* > statsReq; // Required to enter
};

#endif // WEIGHTS_H
