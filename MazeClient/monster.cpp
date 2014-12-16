#include "monster.h"

monster::monster()
{
    //playerAdvanced(0);
}

void monster::playerAdvanced(int level)
{
    while ( the_rooms.rooms[MonsterLevel = level][(MonsterRoom = ((rand()%54)+1))]->getItems().size() == 0 );
    // keep running till we get a room that has an item in it at which to start;
    MonsterDirection = (DIRECTION)(rand()%4); // point monster at some direction
}

void monster::PlayerMoved(int location)
{
    PlayerRoom = location;
}

void monster::MakeMove()
{

}

void monster::Attack()
{

}

bool monster::canAttack()
{

}


int UniformCostSearch()
{
    // start is MonsterRoom and looking for path to PlayerRoom... return is next room to enter based on path
    int NodeDistances[64]; // dist[]
    int visitedNodes[64];  // Q
    int previous[64];      // previous gets things put in it which should be the next hop /// we can have at most 64 hops, so

    for (int i = 0; i < 64; i++)
        previous[i] = -1;
    for (int i = 0; i < 64; i++)
        visitedNodes[i] = 0;
    for (int i = 0; i < 64; i++)
        NodeDistances[i] = 999;

    NodeDistances[MonsterRoom] = 0;

    while (isQEmpty(visitedNodes))
}

