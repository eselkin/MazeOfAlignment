#include "monster.h"

monster::monster(QObject *parent) :
    QObject(parent), MonsterType(0)
{
    QString HLTH=tr("Health"), DMG=tr("Damage");
    MonsterStats.insert(&HLTH, 100); // same for all monsters
    MonsterStats.insert(&DMG, 5); // this will change for monster types in their constructors
    playerAdvanced(0); // same for all monsters
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
    if (PlayerRoom == MonsterRoom)
        Attack();
    else
    {
        vector<int> RoomPath = UniformCostSearch(); // player room
        int PathSize = RoomPath.size();
        if (PathSize > 1)
            MonsterRoom = RoomPath[PathSize-2];
        qDebug() << " MONSTER ROOM: " << MonsterRoom << " PLAYER: " << PlayerRoom <<endl;
    }
}

void monster::Attack()
{
    qDebug () << "ATTACKING!" << endl;
    emit DamagePlayer(MonsterStats["Damage"]);
}

bool monster::canAttack()
{
}

bool monster::regenerate()
{
    QString HLTH=tr("Health");
    MonsterStats.insert(&HLTH, 100);
    playerAdvanced(MonsterLevel); // respawn
}


bool monster::TakeDamage(int damage)
{
    qDebug() << "TAKING DAMAGE IN MONSTER" <<endl;
    QString HLTH=tr("Health");
    MonsterStats.insert(&HLTH, -1*damage);
    if ( MonsterStats[HLTH] <= 0 )
        regenerate();
}

int monster::getRoom()
{
    return MonsterRoom;
}

int monster::getType()
{
    return MonsterType;
}


vector<int> monster::UniformCostSearch()
{
    int NUM_VERTICIES = 64;
    // A Dijkstra method with weights all 1 or NULL

    // start is MonsterRoom and looking for path to PlayerRoom... return is next room to enter based on path
    vector<int> NodeDistances; // dist[]
    bool SPTreeset[64];        // Q? Shortest Paths T/F
    vector<int> previous;      // previous gets things put in it which should be the next hop /// we can have at most 64 hops, so

    // GOTTA FIGURE OUT HOW TO STORE PREVIOUS SO WE CAN KEEP A PATH


    for (int i = 0; i < NUM_VERTICIES; i++)
    {
        NodeDistances.push_back(INFINITY);
        SPTreeset[i] = false;
    }
    NodeDistances[PlayerRoom] = 0; // my starting point to myself is myself
    previous.clear();
    int vertex = PlayerRoom; // can't be player room... Except watch out before player moves... but since move only gets called after player moves...
    // entering into loop
    while (vertex != MonsterRoom)
    {
        // just search for shortest route (fewest jumps) to Player Location
        vertex = ShortestDistance(NodeDistances, SPTreeset); // returns vertex not already set in SPTreeset ( after return it is set though )

        if (vertex == 0)
            break;

        previous.push_back(vertex); // keep track of the path from the first vertex match
        FindNextDistances(NodeDistances, vertex);
    }
    return previous;
}

void monster::FindNextDistances(vector<int> &NodeDistances, int vertex)
{
    int nearest[4] = { vertex-1, vertex-8, vertex+1, vertex+8 };
    for ( int i = 0; i < 4; i++ ) // If it's not NULL (no weight) then uniform weight
        (AdjTable.getWeight(vertex, nearest[i], MonsterLevel)) && (NodeDistances[nearest[i]]=(NodeDistances[vertex]+1));  /// adds on to the distance to the prior vertex point
}

int monster::ShortestDistance(vector<int>& Distances, bool Paths[])
{
    int i = 9;
    int NUM_VERTICES = Distances.size();
    int current_shortest = 0; // just start at the beginning always... probably not efficient
    for (; i < NUM_VERTICES; i++)
        ((Distances[i] < Distances[current_shortest]) && (!Paths[i])) && (current_shortest = i) && (Paths[i] = true);
    // check if it's in Paths, if not, set it to true and make it the current shortest
    return current_shortest;
}
