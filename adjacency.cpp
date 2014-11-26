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
    adjacencytable[0][0][1] = new weights();
    adjacencytable[0][0][1]->addItem("blue key", "key_blue");
    adjacencytable[0][0][1]->addStat("health", 100);
    adjacencytable[0][0][1]->addStat("alignment", 0); // 0-8... 0=Lawful Good
    adjacencytable[0][1][0] = new weights();
    adjacencytable[0][1][0]->addItem("blue key", "key_blue");
    adjacencytable[0][1][0]->addStat("health", 50);   // cannot go back with no Health
    adjacencytable[0][1][0]->addStat("alignment", 0); // 0-8... 0=Lawful Good .. to go back to the beginning you must be LG
    adjacencytable[0][1][2] = new weights();
    adjacencytable[0][2][3] = new weights();
    adjacencytable[0][2][8] = new weights();
    adjacencytable[0][8][2] = new weights();
    adjacencytable[0][8][9] = new weights();
    adjacencytable[0][9][8] = new weights();
    adjacencytable[0][3][9] = new weights();
    adjacencytable[0][9][3] = new weights();
    adjacencytable[0][9][10] = new weights();
    adjacencytable[0][10][9] = new weights();
    adjacencytable[0][10][11] = new weights();
    adjacencytable[0][11][10] = new weights();
    adjacencytable[0][5][11] = new weights();
    adjacencytable[0][11][5] = new weights();
    adjacencytable[0][8][14] = new weights();
    adjacencytable[0][14][8] = new weights();
    adjacencytable[0][8][14] = new weights();
    adjacencytable[0][14][20] = new weights();
    adjacencytable[0][20][14] = new weights();
    adjacencytable[0][19][20] = new weights();
    adjacencytable[0][20][19] = new weights();
    adjacencytable[0][19][13] = new weights();
    adjacencytable[0][21][20] = new weights();
    adjacencytable[0][21][20] = new weights();
    adjacencytable[0][22][21] = new weights();
    adjacencytable[0][21][22] = new weights();
    adjacencytable[0][22][23] = new weights();
    adjacencytable[0][23][22] = new weights();
    adjacencytable[0][23][29] = new weights();
    adjacencytable[0][29][23] = new weights();
    adjacencytable[0][29][28] = new weights();
    adjacencytable[0][28][29] = new weights();
    adjacencytable[0][28][27] = new weights();
    adjacencytable[0][27][28] = new weights();
    adjacencytable[0][27][26] = new weights();
    adjacencytable[0][26][27] = new weights();
    adjacencytable[0][26][25] = new weights();
    adjacencytable[0][25][26] = new weights();
    adjacencytable[0][26][32] = new weights();
    adjacencytable[0][32][26] = new weights();
    adjacencytable[0][32][31] = new weights();
    adjacencytable[0][31][32] = new weights();
    adjacencytable[0][31][30] = new weights();
    adjacencytable[0][30][31] = new weights();

    //Level1

}

Adjacency::~Adjacency()
{

}

weights *Adjacency::getWeight(int room_num, int next_room, int current_level)
{
    std::cout << "ERROR: " << room_num << " AND : " << next_room << " NAND " << endl;
    if (room_num < 9 || room_num > 54)
        return NULL;
    // public function
    return adjacencytable[current_level][room_num][next_room]; // even if NULL
}
