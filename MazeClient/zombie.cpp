#include "zombie.h"

zombie::zombie()
{
    // Now we have a zombie
    MonsterImage.load("zombie.png");
    MonsterWeapon = theItems.itemlist["weapon_spear"];
    MonsterType = "Zombie";
}
