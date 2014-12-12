#ifndef MONSTER_H
#define MONSTER_H
#include <QVector>
#include <QImage>
#include <QString>
#include "stats.h"
#include "items.h"
#include "allItems.h"
#include "bst.h"

class monster
{
public:
    monster();

public slots:
    void MakeMove();
    void Attack();

protected:
    bst<string> MonsterStats;
    items* MonsterWeapon;
    QImage MonsterImage;
    int MonsterRoom;
    int MonsterLevel;
    allItems theItems;

private:
    QString MonsterType;

};

#endif // MONSTER_H
