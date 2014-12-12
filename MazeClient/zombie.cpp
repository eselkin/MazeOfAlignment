#include "zombie.h"

zombie::zombie() : MonsterType("Zombie")
{
    // Now we have a zombie
    MonsterImage.load("zombie.png");
    MonsterWeapon = theItems.itemlist["weapon_spear"];

}
