#include "monster.h"

monster::monster()
{
    playerAdvanced(0);
}

void monster::playerAdvanced(int level)
{
    while ( the_rooms[MonsterLevel = level][(MonsterRoom = ((rand()%54)+1))].getItems().size() == 0 );
    // keep running till we get a room that has an item in it at which to start;
}

void monster::PlayerMoved(int location)
{

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
