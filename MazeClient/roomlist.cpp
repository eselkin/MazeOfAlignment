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
    rooms[1][54]->addItem(listofitems.itemlist["key_blue"]);
    rooms[1][22]->addItem(listofitems.itemlist["key_red"]);
    rooms[1][21]->addItem(listofitems.itemlist["weapon_axe"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_gold"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_black"]);
    rooms[1][17]->addItem(listofitems.itemlist["weapon_spear"]);


    Question* q1 = new Question;
    q1->changeQuestion("You chose the weapon you're currently wielding because:");
    q1->addAnswer("a. It is has the greatest potential for POWERRRR");
    q1->addStat("Evil",5,"Chaotic",5);
    q1->addAnswer("b. It is a standard and law-abiding weapon, reliable in all situations");
    q1->addStat("Lawful",20, "Good", 20);
    q1->addAnswer("c. It is the best for taking advantage of opportune moments");
    q1->addStat("Neutral",5, "Chaotic", 5);
    q1->addAnswer("d. It smashes things standing in my way");
    q1->addStat("Chaotic",10, "Evil", 1);
    rooms[1][9]->addQuestion(q1);

//    Question* q2 = new Question;
//    q2->changeQuestion("You need to cross a narrow bridge currently being guarded by a 'Black Knight.' How do you approach this obstacle?");
//    q2->addAnswer("a. Challenge the Black Knight to a duel to death");
//    q2->addStat("Chaotic",5);
//    q2->addAnswer("b. Invite the Black Knight to join your quest, using reason and honorable incentives to persuade him.");
//    q2->addStat("Good",5);
//    q2->addAnswer("c. Sneak up on him and assassinate him; there is no such thing as an unfair advantage!");
//    q2->addStat("Evil",10);
//    q2->addAnswer("d. Snipe him (with whatever means) from far away; if he chases, he's no longer blocking the bridge, and if he doesn't, you'll just keep sniping!");
//    q2->addStat("Evil",5);
//    rooms[1][19]->addQuestion(q2);

//    Question* q3 = new Question;
//    q3->changeQuestion("You find your way blocked by a locked door. You...");
//    q3->addAnswer("a. Look for the key in logical places");
//    q3->addStat("Lawful",5);
//    q3->addAnswer("b. Pick the lock");
//    q3->addStat("Neutral",5);
//    q3->addAnswer("c. Kick it or knock it down");
//    q3->addStat("Chaotic",5);
//    q3->addAnswer("d. Knock nicely?");
//    q3->addStat(new stats("Good",10));
//    rooms[1][28]->addQuestion(q3);

//    Question* q4 = new Question;
//    q4->changeQuestion("You've been persuaded to give a loan to a friend of a friend. You...");
//    q4->addAnswer("a. Write up a contract, recording all the terms and the signatures of all parties");
//    q4->addStat(new stats("Lawful",25));
//    q4->addAnswer("b. Make it known you expect to be repaid, but keep the terms flexible");
//    q4->addStat(new stats("Good",5));
//    q4->addAnswer("c. Charged interest");
//    q4->addStat(new stats("Neutral",5));
//    q4->addAnswer("d. Don't care about the exact amount; they just owe you a favor later");
//    q4->addStat(new stats("Chaotic",2));
//    rooms[1][42]->addQuestion(q4);

//    Question* q5 = new Question;
//    q5->changeQuestion("Your family disapproves of your significant other because of philosophical/religious/family feud reasons. You...");
//    q5->addAnswer("a. Keep your silence, evade their questions, and don’t really care what they think");
//    q5->addStat(new stats("Neutral",5));
//    q5->addAnswer("b. Go back and forth to try to explain get both sides to compromise");
//    q5->addStat(new stats("Lawful",5));
//    q5->addAnswer("c. Respect your family’s wishes and break off your relationship");
//    q5->addStat(new stats("Good",5));
//    q5->addAnswer("d. Openly and defiantly declare your love for your significant other and publicly propose marriage");
//    q5->addStat(new stats("Chaotic",4));
//    rooms[1][54]->addQuestion(q5);

//    Question* q6 = new Question;
//    q6->changeQuestion("Do you respect the laws and the authorities of your community?");
//    q6->addAnswer("a. Yes, unerringly!");
//    q6->addStat(new stats("Lawful",25));
//    q6->addAnswer("b. Yes, rules are necessary for society to function, even though you know power corrupts and some people take advantage of the rules");
//    q6->addStat(new stats("Good",10));
//    q6->addAnswer("c. If it suits you to; there are some laws you can’t agree with and/or cannot respect");
//    q6->addStat(new stats("Neutral",10));
//    q6->addAnswer("d. You have a problem with authority and/or you break rules to break them");
//    q6->addStat(new stats("Chaotic",25));
////    rooms[1][54]->addQuestion(q6);

//    Question* q7 = new Question;
//    q7->changeQuestion("What is the best use of excess wealth?");
//    q7->addAnswer("a. There is no such thing; use it to obtain more wealth");
//    q7->addStat(new stats("Neutral",15));
//    q7->addAnswer("b. Help those in need of money");
//    q7->addStat(new stats("Good",5));
//    q7->addAnswer("c. Use it to prevent others from obtaining similar wealth");
//    q7->addStat(new stats("Evil",20));
//    q7->addAnswer("d. Spend it on yourself, your family, and/or friends");
//    q7->addStat(new stats("Neutral",5));
////    rooms[1][54]->addQuestion(q7);
}

roomlist::~roomlist()
{
    for (uint i = 0; i <7; i++)
    {
        for (uint j = 0; j < 64; j++)
            delete rooms[i][j];
    }
}
