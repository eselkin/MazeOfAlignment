#include "roomlist.h"


roomlist::roomlist()
{
    for (uint i = 0; i < 7; i++)
    {
        for (uint j = 0; j < 64; j++)
            rooms[i][j] = new room();
    }

    rooms[0][9]->addItem(listofitems.itemlist["key_black"]);
    rooms[1][49]->addItem(listofitems.itemlist["orb_win"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_gold"]);
    rooms[1][17]->addItem(listofitems.itemlist["orb_win"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_black"]);
    rooms[1][17]->addItem(listofitems.itemlist["weapon_spear"]);


    Question* q1 = new Question;
    q1->changeQuestion("You chose the weapon you're currently wielding because:");
    q1->addAnswer("a. It is has the greatest potential for POWERRRR");
    q1->addStat(new stats("Evil",5));
    q1->addAnswer("b. It is a standard and law-abiding weapon, reliable in all situations");
    q1->addStat(new stats("Lawful",5));
    q1->addAnswer("c. It is the best for taking advantage of opportune moments");
    q1->addStat(new stats("Neutral",5));
    q1->addAnswer("d. It smashes things standing in my way");
    q1->addStat(new stats("Chaotic",5));
    rooms[1][9]->addQuestion(q1);


}

roomlist::~roomlist()
{
    for (uint i = 0; i <7; i++)
    {
        for (uint j = 0; j < 64; j++)
            delete rooms[i][j];
    }
}
