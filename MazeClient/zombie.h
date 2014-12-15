#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "monster.h"

class zombie : public monster
{
public:
    zombie();

    // privates from protected of monster
public slots:
    void MakeMove();
    void Attack();

};

#endif // ZOMBIE_H
