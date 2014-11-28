#include "adjacency.h"
#include <iostream>
Adjacency::Adjacency()
{
    // Create Levels here

    // BLOCKED BOXES
    for (uint i = 0; i < 7; i++)
        for (uint j = 0; j < 64; j++)
            for (uint k = 0; k < 64; k++)
                adjacencytable[i][j][k] = NULL;

    //Level0
    adjacencytable[0][9][10] = new weights();
    adjacencytable[0][9][10]->setDoor(0);
    adjacencytable[0][9][10]->addItem("blue key", "key_blue");
    adjacencytable[0][9][10]->addStat("health", 100);
    adjacencytable[0][9][10]->addStat("alignment", 0); // 0-8... 0=Lawful Good
    adjacencytable[0][10][9] = new weights();
    adjacencytable[0][10][9]->setDoor(0);
    adjacencytable[0][10][9]->addItem("blue key", "key_blue");
    adjacencytable[0][10][9]->addStat("health", 50);   // cannot go back with no Health
    adjacencytable[0][10][9]->addStat("alignment", 0); // 0-8... 0=Lawful Good .. to go back to the beginning you must be LG
    adjacencytable[0][10][11] = new weights();
    adjacencytable[0][11][10] = new weights();
    adjacencytable[0][11][19] = new weights();
    adjacencytable[0][11][19]->setDoor(2);
    adjacencytable[0][19][11] = new weights();
    adjacencytable[0][19][20] = new weights();
    adjacencytable[0][20][19] = new weights();
    adjacencytable[0][19][27] = new weights();
    adjacencytable[0][27][19] = new weights();
    adjacencytable[0][20][12] = new weights();
    adjacencytable[0][12][20] = new weights();
    adjacencytable[0][20][21] = new weights();
    adjacencytable[0][21][20] = new weights();
    adjacencytable[0][21][22] = new weights();
    adjacencytable[0][22][21] = new weights();
    adjacencytable[0][22][14] = new weights();
    adjacencytable[0][14][22] = new weights();
    adjacencytable[0][27][35] = new weights();
    adjacencytable[0][35][27] = new weights();
    adjacencytable[0][35][34] = new weights();
    adjacencytable[0][34][35] = new weights();
    adjacencytable[0][34][26] = new weights();
    adjacencytable[0][26][34] = new weights();
    adjacencytable[0][35][36] = new weights();
    adjacencytable[0][36][35] = new weights();
    adjacencytable[0][36][37] = new weights();
    adjacencytable[0][37][36] = new weights();
    adjacencytable[0][37][38] = new weights();
    adjacencytable[0][38][37] = new weights();
    adjacencytable[0][38][46] = new weights();
    adjacencytable[0][46][38] = new weights();
    adjacencytable[0][46][45] = new weights();
    adjacencytable[0][45][46] = new weights();
    adjacencytable[0][45][44] = new weights();
    adjacencytable[0][44][45] = new weights();
    adjacencytable[0][44][43] = new weights();
    adjacencytable[0][43][44] = new weights();
    adjacencytable[0][43][51] = new weights();
    adjacencytable[0][51][43] = new weights();
    adjacencytable[0][43][42] = new weights();
    adjacencytable[0][42][43] = new weights();
    adjacencytable[0][51][50] = new weights();
    adjacencytable[0][50][51] = new weights();
    adjacencytable[0][50][49] = new weights();
    adjacencytable[0][49][50] = new weights();

    //Level1

}

Adjacency::~Adjacency()
{

}

weights *Adjacency::getWeight(int room_num, int next_room, int current_level)
{
    if (room_num < 9 || room_num > 54)
        return NULL;
    // public function
    return adjacencytable[current_level][room_num][next_room]; // even if NULL
}
