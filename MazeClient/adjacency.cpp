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
    adjacencytable[0][9][10]->addItem("blue key", "key_blue");
    adjacencytable[0][9][10]->addItem("black key", "key_black");
    adjacencytable[0][9][10]->addItem("red key", "key_red");
    adjacencytable[0][9][10]->addStat("Evil", 5, "Lawful", 5); // 0-8... 0=Lawful Good
    adjacencytable[0][10][9] = new weights();
    adjacencytable[0][10][9]->addItem("blue key", "key_blue");
    adjacencytable[0][10][9]->addStat("Health", 50,"Strength", 100);   // cannot go back with no Health
    adjacencytable[0][10][9]->addStat("Good", 20, "Lawful", 20); // 0-8... 0=Lawful Good .. to go back to the beginning you must be LG
    adjacencytable[0][10][11] = new weights();
    adjacencytable[0][11][10] = new weights();
    adjacencytable[0][11][19] = new weights();
    adjacencytable[0][11][19]->setDoor(2);
    adjacencytable[0][19][11] = new weights();
    adjacencytable[0][19][20] = new weights();
    adjacencytable[0][19][20]->setDoor(1);
    adjacencytable[0][20][19] = new weights();
    adjacencytable[0][19][27] = new weights();
    adjacencytable[0][19][27]->setDoor(1);
    adjacencytable[0][27][19] = new weights();
    adjacencytable[0][20][12] = new weights();
    adjacencytable[0][12][20] = new weights();
    adjacencytable[0][20][21] = new weights();
    adjacencytable[0][21][20] = new weights();
    adjacencytable[0][21][22] = new weights();
    adjacencytable[0][22][21] = new weights();
    adjacencytable[0][22][14] = new weights();
    adjacencytable[0][22][14]->setDoor(2);
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
    adjacencytable[0][37][38]->setDoor(2);
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
    adjacencytable[1][9][10] = new weights();
    adjacencytable[1][10][9] = new weights();
    adjacencytable[1][10][9]->addStat("Good", 20, "Lawful", 20); // 0-8... 0=Lawful Good .. to go back to the beginning you must be LG
    adjacencytable[1][9][17] = new weights();
    adjacencytable[1][9][17]->addItem("gold_key", "key_gold");
    adjacencytable[1][9][17]->addItem("black_key", "key_black");
    adjacencytable[1][17][9] = new weights();
    adjacencytable[1][17][9]->addItem("gold_key", "key_gold");
    adjacencytable[1][17][9]->setDoor(3);
    adjacencytable[1][9][17]->setDoor(3);
    adjacencytable[1][17][18] = new weights();
    adjacencytable[1][17][18]->setDoor(3);
    adjacencytable[1][18][17] = new weights();
    adjacencytable[1][18][17]->setDoor(3);
    adjacencytable[1][17][18]->setDoor(4);
    adjacencytable[1][18][17]->setDoor(4);
    adjacencytable[1][18][19] = new weights();
    adjacencytable[1][19][18] = new weights();
    adjacencytable[1][11][19] = new weights();
    adjacencytable[1][19][11] = new weights();
    adjacencytable[1][11][10] = new weights();
    adjacencytable[1][11][12] = new weights();
    adjacencytable[1][12][11] = new weights();
    adjacencytable[1][12][20] = new weights();
    adjacencytable[1][20][12] = new weights();
    adjacencytable[1][20][28] = new weights();
    adjacencytable[1][28][27] = new weights();
    adjacencytable[1][27][28] = new weights();
    adjacencytable[1][27][26] = new weights();
    adjacencytable[1][26][25] = new weights();
    adjacencytable[1][25][26] = new weights();
    adjacencytable[1][25][17] = new weights();
    adjacencytable[1][17][25] = new weights();
    adjacencytable[1][25][33] = new weights();
    adjacencytable[1][33][25] = new weights();
    adjacencytable[1][33][34] = new weights();
    adjacencytable[1][34][33] = new weights();
    adjacencytable[1][34][33]->setDoor(5);
    adjacencytable[1][33][34]->setDoor(5);
    adjacencytable[1][33][41] = new weights();
    adjacencytable[1][41][33] = new weights();
    adjacencytable[1][41][42] = new weights();
    adjacencytable[1][42][41] = new weights();
    adjacencytable[1][41][42]->setDoor(2);
    adjacencytable[1][42][41]->setDoor(2);
    adjacencytable[1][42][34] = new weights();
    adjacencytable[1][42][43] = new weights();
    adjacencytable[1][43][42] = new weights();
    adjacencytable[1][44][43] = new weights();
    adjacencytable[1][43][44] = new weights();
    adjacencytable[1][44][45] = new weights();
    adjacencytable[1][45][44] = new weights();
    adjacencytable[1][45][37] = new weights();
    adjacencytable[1][37][45] = new weights();
    adjacencytable[1][37][29] = new weights();
    adjacencytable[1][29][37] = new weights();
    adjacencytable[1][29][21] = new weights();
    adjacencytable[1][21][29] = new weights();
    adjacencytable[1][21][22] = new weights();
    adjacencytable[1][22][21] = new weights();
    adjacencytable[1][21][22]->setDoor(4);
    adjacencytable[1][22][21]->setDoor(4);
    adjacencytable[1][22][30] = new weights();
    adjacencytable[1][30][38] = new weights();
    adjacencytable[1][38][30] = new weights();
    adjacencytable[1][38][46] = new weights();
    adjacencytable[1][46][38] = new weights();
    adjacencytable[1][46][54] = new weights();
    adjacencytable[1][54][46] = new weights();
    adjacencytable[1][54][53] = new weights();
    adjacencytable[1][53][54] = new weights();
    adjacencytable[1][53][52] = new weights();
    adjacencytable[1][52][53] = new weights();
    adjacencytable[1][52][51] = new weights();
    adjacencytable[1][51][52] = new weights();
    adjacencytable[1][51][43] = new weights();
    adjacencytable[1][51][50] = new weights();
    adjacencytable[1][50][51] = new weights();
    adjacencytable[1][49][50] = new weights();
    adjacencytable[1][50][49] = new weights();


    //Level2
    adjacencytable[2][22][14] = new weights();
    adjacencytable[2][22][14]->addItem("Gold key", "key_gold");
    adjacencytable[2][22][14]->setDoor(4);
    adjacencytable[2][14][22] = new weights();
    adjacencytable[2][14][22]->setDoor(4);
    adjacencytable[2][22][30] = new weights();
    adjacencytable[2][22][30]->addStat("Good", 50, "Lawful", 20);
    adjacencytable[2][22][30]->setDoor(4);
    adjacencytable[2][30][22] = new weights();
    adjacencytable[2][30][22]->addStat("Good", 100, "Lawful", 20);
    adjacencytable[2][30][22]->setDoor(4);
    adjacencytable[2][30][38] = new weights();
    adjacencytable[2][38][30] = new weights();
    adjacencytable[2][38][46] = new weights();
    adjacencytable[2][46][38] = new weights();
    adjacencytable[2][46][45] = new weights();
    adjacencytable[2][45][46] = new weights();
    adjacencytable[2][45][46]->setDoor(2);
    adjacencytable[2][45][46]->addStat("Good", 100, "Evil", 20);
    adjacencytable[2][45][37] = new weights();
    adjacencytable[2][37][45] = new weights();
    adjacencytable[2][37][29] = new weights();
    adjacencytable[2][29][37] = new weights();
    adjacencytable[2][29][28] = new weights();
    adjacencytable[2][28][29] = new weights();
    adjacencytable[2][28][36] = new weights();
    adjacencytable[2][36][28] = new weights();
    adjacencytable[2][36][44] = new weights();
    adjacencytable[2][44][36] = new weights();
    adjacencytable[2][44][52] = new weights(); // END OF GAME HERE
    adjacencytable[2][44][52]->setDoor(3);
    adjacencytable[2][44][52]->addItem("Blue key", "key_blue");
    adjacencytable[2][44][52]->addStat("Evil", 60, "Chaotic", 30); // You have to be really evil to go the short way
    adjacencytable[2][52][44] = new weights();
    adjacencytable[2][52][44]->setDoor(3);
    adjacencytable[2][52][44]->addItem("Blue key", "key_blue");
    adjacencytable[2][14][13] = new weights();
    adjacencytable[2][14][13]->setDoor(1);
    adjacencytable[2][14][13]->addItem("Silver key", "key_silver");
    adjacencytable[2][13][14] = new weights();
    adjacencytable[2][13][14]->setDoor(1);
    adjacencytable[2][13][12] = new weights();
    adjacencytable[2][12][13] = new weights();
    adjacencytable[2][12][11] = new weights();
    adjacencytable[2][12][11]->setDoor(3);
    adjacencytable[2][12][11]->addItem("Red key", "key_red");
    adjacencytable[2][11][12] = new weights();
    adjacencytable[2][11][12]->setDoor(3);
    adjacencytable[2][11][12]->addItem("Red key", "key_red");
    adjacencytable[2][11][10] = new weights();
    adjacencytable[2][10][11] = new weights();
    adjacencytable[2][10][9] = new weights();
    adjacencytable[2][10][9]->setDoor(5);
    adjacencytable[2][10][9]->addStat("Lawful", 30, "Neutral", 25);
    adjacencytable[2][9][10] = new weights();
    adjacencytable[2][9][10]->setDoor(5);
    adjacencytable[2][9][17] = new weights();
    adjacencytable[2][9][17]->setDoor(3);
    adjacencytable[2][17][9] = new weights();
    adjacencytable[2][17][9]->setDoor(3);
    adjacencytable[2][17][25] = new weights();
    adjacencytable[2][25][17] = new weights();
    adjacencytable[2][17][25] = new weights();
    adjacencytable[2][25][33] = new weights();
    adjacencytable[2][33][25] = new weights();
    adjacencytable[2][33][41] = new weights();
    adjacencytable[2][33][41]->setDoor(2);
    adjacencytable[2][41][33] = new weights();
    adjacencytable[2][41][33]->setDoor(2);
    adjacencytable[2][41][33]->addItem("Blue key", "key_blue");
    adjacencytable[2][41][49] = new weights();
    adjacencytable[2][41][49]->setDoor(4);
    adjacencytable[2][49][41] = new weights();
    adjacencytable[2][49][41]->setDoor(4);

    //
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
