#ifndef ADJACENCY_H
#define ADJACENCY_H
#include "weights.h"

typedef unsigned int uint;

class Adjacency
{
public:
    Adjacency();
    ~Adjacency();

private:
    weights* adjacencytable[7][36][36]; // 7 levels of 36x36 weighted adjacencies for 36 rooms per level
};

Adjacency::Adjacency()
{
    // Create Levels here

    // BLOCKED BOXES
    for (uint i = 0; i < 7; i++)
        for (uint j = 0; j < 36; j++)
            adjacencytable[i][j][j] = NULL;

    //Level0
    adjacencytable[0][0][1] = new weights();
    adjacencytable[0][0][1]->addItem("blue key", "key_blue");
}

#endif // ADJACENCY_H
