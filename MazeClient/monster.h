#ifndef MONSTER_H
#define MONSTER_H
#include <QVector>
#include <QImage>
#include <QString>
#include "items.h"
#include "allItems.h"
#include "bst.h"
#include "networkofalignment.h"
#include "roomlist.h"
#include "adjacency.h"

enum DIRECTION { EAST, WEST, NORTH, SOUTH };

class monster
{
public:
    monster();

public slots:
    void PlayerMoved(int location);
    void playerAdvanced(int level);
    void MakeMove();
    void Attack();
    bool canAttack();
    void TakeDamage(int damage);

public signals:
    void DamagePlayer(int damage);

protected:
    vector<int>& UniformCostSearch();
    void FindNextDistances(vector<int> &NodeDistances, int vertex);  // updates node distances from current vertex with shortest distance
    int ShortestDistance(vector<int> &Distances, bool Paths[]);
    bst<string> MonsterStats;
    items* MonsterWeapon;
    QImage MonsterImage;
    int PlayerRoom;
    int MonsterRoom;
    int MonsterLevel;
    DIRECTION MonsterDirection;
    allItems theItems;
    bst<QString> mystats;
    QString MonsterType;
    roomlist the_rooms;
    Adjacency AdjTable;
private:

};

#endif // MONSTER_H
