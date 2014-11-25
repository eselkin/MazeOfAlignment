#include "adjacency.h"

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
    adjacencytable[0][0][1]->addStat("health", 100);
}


