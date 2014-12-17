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


int monster::UniformCostSearch()
{
    int NUM_VERTICIES = 64;
    // A Dijkstra method with weights all 1 or NULL

    // start is MonsterRoom and looking for path to PlayerRoom... return is next room to enter based on path
    vector<int> NodeDistances; // dist[]
    vector<int> SPTreeset;  // Q? Shortest Paths
    vector<int> previous;      // previous gets things put in it which should be the next hop /// we can have at most 64 hops, so

    for (int i = 0; i < NUM_VERTICIES; i++)
        NodeDistances.push_back(INFINITY);
    NodeDistances[MonsterRoom] = 0; // my starting point to myself is myself
    SPTreeset.clear();
    previous.clear();
    int vertex = ShortestDistance(NodeDistances, SPTreeset);
    FindNextDistances(NodeDistances, vertex);
}

void monster::FindNextDistances(vector<int> &NodeDistances, int vertex)
{

}

int monster::ShortestDistance(vector<int>& Distances, vector<int>& Paths)
{
    int i = 0;
    int NUM_VERTICES = Distances.size();
    int current_shortest = 0;
    for (; i < NUM_VERTICES; i++)
        (Distances[i] < Distances[current_shortest]) && (current_shortest = i);
    Paths.push_back(current_shortest);
    return current_shortest;
}
