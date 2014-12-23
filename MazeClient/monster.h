#ifndef MONSTER_H
#define MONSTER_H
#include <QVector>
#include <QImage>
#include <QObject>
#include <QString>
#include "items.h"
#include "allItems.h"
#include "bst.h"
#include "networkofalignment.h"
#include "roomlist.h"
#include "adjacency.h"

enum DIRECTION { EAST, WEST, NORTH, SOUTH };

class monster : public QObject
{
    Q_OBJECT
public:
    explicit monster(QObject *parent = 0);

public slots:
    void PlayerMoved(int location);
    void playerAdvanced(int level);
    void MakeMove();
    void Attack();
    bool canAttack();
    bool TakeDamage(int damage);
    int getRoom();
    int getType();
    bool regenerate();

signals:
    void DamagePlayer(int damage);

protected:
    vector<int> UniformCostSearch();
    void FindNextDistances(vector<int> &NodeDistances, int vertex);  // updates node distances from current vertex with shortest distance
    int ShortestDistance(vector<int> &Distances, bool Paths[]);
    bst<string> MonsterStats;
    items* MonsterWeapon;
    QImage MonsterImage;
    int PlayerRoom;
    int MonsterRoom;
    int MonsterLevel;
    int MonsterType;
    DIRECTION MonsterDirection;
    allItems theItems;
    bst<QString> mystats;
    roomlist the_rooms;
    Adjacency AdjTable;

private:

};

#endif // MONSTER_H
