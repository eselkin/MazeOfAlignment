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

protected:
    bst<string> MonsterStats;
    items* MonsterWeapon;
    QImage MonsterImage;
    int PlayerRoom;
    int MonsterRoom;
    int MonsterLevel;
    allItems theItems;
    bst<QString> mystats;
    QString MonsterType;
    int startlocations[10];
    roomlist the_rooms;
private:

};

#endif // MONSTER_H
