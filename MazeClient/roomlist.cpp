#include "roomlist.h"


roomlist::roomlist()
{
    for (uint i = 0; i < 7; i++)
    {
        for (uint j = 0; j < 64; j++)
            rooms[i][j] = new room();
    }

    rooms[0][9]->addItem(listofitems.itemlist["key_black"]);
    rooms[0][9]->addItem(listofitems.itemlist["key_blue"]);
    rooms[0][9]->addItem(listofitems.itemlist["key_red"]);
    rooms[0][9]->addItem(listofitems.itemlist["key_silver"]);
    rooms[0][49]->addItem(listofitems.itemlist["orb_win"]);

    rooms[1][49]->addItem(listofitems.itemlist["orb_win"]);
    rooms[1][54]->addItem(listofitems.itemlist["key_blue"]);
    rooms[1][22]->addItem(listofitems.itemlist["key_red"]);
    rooms[1][21]->addItem(listofitems.itemlist["weapon_axe"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_gold"]);
    rooms[1][17]->addItem(listofitems.itemlist["key_black"]);
    rooms[1][17]->addItem(listofitems.itemlist["weapon_spear"]);

    rooms[2][14]->addItem(listofitems.itemlist["key_red"]);
    rooms[2][14]->addItem(listofitems.itemlist["key_silver"]);
    rooms[2][10]->addItem(listofitems.itemlist["key_blue"]); // the only blue key
    rooms[2][25]->addItem(listofitems.itemlist["weapon_spear"]);
    rooms[2][49]->addItem(listofitems.itemlist["key_black"]);


    Question* q6 = new Question;
    q6->changeQuestion("Do you respect the laws and the authorities of your community?");
    q6->addAnswer("a. Yes, unerringly!");
    q6->addStat("Lawful",25, "Good", 5);
    q6->addAnswer("b. Yes, rules are necessary for society to function, even though you know power corrupts and some people take advantage of the rules");
    q6->addStat("Good",15, "Lawful", 5);
    q6->addAnswer("c. If it suits you to; there are some laws you can't agree with and/or cannot respect");
    q6->addStat("Neutral",10, "Chaotic", 5);
    q6->addAnswer("d. You have a problem with authority and/or you break rules to break them");
    q6->addStat("Chaotic",25, "Evil", 3);
    rooms[0][10]->addQuestion(q6);

    Question* q7 = new Question;
    q7->changeQuestion("What is the best use of excess wealth?");
    q7->addAnswer("a. There is no such thing; use it to obtain more wealth");
    q7->addStat("Neutral",15, "Evil", 1);
    q7->addAnswer("b. Help those in need of money");
    q7->addStat("Good",15);
    q7->addAnswer("c. Use it to prevent others from obtaining similar wealth");
    q7->addStat("Evil",20);
    q7->addAnswer("d. Spend it on yourself, your family, and/or friends");
    q7->addStat("Neutral",5);
    rooms[0][21]->addQuestion(q7);

    Question* q8 = new Question;
    q8->changeQuestion("A beggar approaches you. You...");
    q8->addAnswer("a. Give generously");
    q8->addStat("Good",15);
    q8->addAnswer("b. Give your spare change; you wouldn't miss it");
    q8->addStat("Good",5);
    q8->addAnswer("c. Try to avoid him and ignore him when you pass");
    q8->addStat("Evil",7);
    q8->addAnswer("d. Throw him an insult as you pass");
    q8->addStat("Evil",20, "Chaotic", 7);
    rooms[0][38]->addQuestion(q8);

    Question* q9 = new Question;
    q9->changeQuestion("If your wizard friend taught you how to fool merchants into thinking copper pieces were gold pieces, you would...");
    q9->addAnswer("a. Use it whenever you can, but don't go out of your way to buy things you wouldn't normally want");
    q9->addStat("Neutral",10);
    q9->addAnswer("b. Cheat only the rich merchants and/or when buying something expensive");
    q9->addStat("Neutral",5, "Good", 2);
    q9->addAnswer("c. Never use it. That's dishonest!");
    q9->addStat("Good",10, "Lawful", 10);
    q9->addAnswer("d. Use it to turn a huge profit and screw over everyone else");
    q9->addStat("Evil",10, "Chaotic", 10);
    rooms[0][43]->addQuestion(q9);


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

    Question* q2 = new Question;
    q2->changeQuestion("You need to cross a narrow bridge currently being guarded by a 'Black Knight.' How do you approach this obstacle?");
    q2->addAnswer("a. Challenge the Black Knight to a duel to death");
    q2->addStat("Chaotic",5);
    q2->addAnswer("b. Invite the Black Knight to join your quest, using reason and honorable incentives to persuade him.");
    q2->addStat("Good",5);
    q2->addAnswer("c. Sneak up on him and assassinate him; there is no such thing as an unfair advantage!");
    q2->addStat("Evil",10);
    q2->addAnswer("d. Snipe him (with whatever means) from far away; if he chases, he's no longer blocking the bridge, and if he doesn't, you'll just keep sniping!");
    q2->addStat("Evil",5);
    rooms[1][19]->addQuestion(q2);

    Question* q3 = new Question;
    q3->changeQuestion("You find your way blocked by a locked door. You...");
    q3->addAnswer("a. Look for the key in logical places");
    q3->addStat("Lawful",5);
    q3->addAnswer("b. Pick the lock");
    q3->addStat("Neutral",5);
    q3->addAnswer("c. Kick it or knock it down");
    q3->addStat("Chaotic",5);
    q3->addAnswer("d. Knock nicely?");
    q3->addStat("Good",10);
    rooms[1][28]->addQuestion(q3);

    Question* q4 = new Question;
    q4->changeQuestion("You've been persuaded to give a loan to a friend of a friend. You...");
    q4->addAnswer("a. Write up a contract, recording all the terms and the signatures of all parties");
    q4->addStat("Lawful",25);
    q4->addAnswer("b. Make it known you expect to be repaid, but keep the terms flexible");
    q4->addStat("Good",5);
    q4->addAnswer("c. Charged interest");
    q4->addStat("Neutral",5);
    q4->addAnswer("d. Don't care about the exact amount; they just owe you a favor later");
    q4->addStat("Chaotic",2);
    rooms[1][42]->addQuestion(q4);

    Question* q5 = new Question;
    q5->changeQuestion("Your family disapproves of your significant other because of philosophical/religious/family feud reasons. You...");
    q5->addAnswer("a. Keep your silence, evade their questions, and don’t really care what they think");
    q5->addStat("Neutral",10);
    q5->addAnswer("b. Go back and forth to try to explain get both sides to compromise");
    q5->addStat("Lawful",10);
    q5->addAnswer("c. Respect your family's wishes and break off your relationship");
    q5->addStat("Good",10, "Neutral", 10);
    q5->addAnswer("d. Openly and defiantly declare your love for your significant other and publicly propose marriage");
    q5->addStat("Chaotic",5, "Neutral", 5);
    rooms[1][54]->addQuestion(q5);

    Question* q10 = new Question;
    q10->changeQuestion("You see a thief in the process of lifting something from a shop. You...");
    q10->addAnswer("a. Shrug and say nothing. Not your shop, not your problem");
    q10->addStat("Neutral",10);
    q10->addAnswer("b. Tell the shopkeeper on your way out and let him handle it himself");
    q10->addStat("Lawful",10, "Neutral", 5);
    q10->addAnswer("c. Call out the thief loudly, and steal something in the ensuing confusion");
    q10->addStat("Chaotic",10, "Evil", 10);
    q10->addAnswer("d. Sternly confront the thief and dissuade him from his dishonorable ways");
    q10->addStat("Lawful",15, "Good", 15);
    rooms[2][14]->addQuestion(q10);

    Question* q11 = new Question;
    q11->changeQuestion("A very good friend is being picked on, and it looks like it may come to blows. You...");
    q11->addAnswer("a. Let him handle it on his own. It's not your problem and you don't want to deprive your friend the dignity of standing up for himself, but you'll stay nearby to scrape your friend off the road afterwards ");
    q11->addStat("Neutral",20, "Coward", 10);
    q11->addAnswer("b. Quickly look for an authority figure to break up the fight");
    q11->addStat("Lawful",10, "Neutral", 5);
    q11->addAnswer("c. Stand up for your friend yourself, knowing you'll likely get beat up with him");
    q11->addStat("Chaotic",5, "Good", 5);
    q11->addAnswer("d. Wait until it comes to blows before sneaking up and knocking out the aggressors from behind");
    q11->addStat("Chaotic", 2);
    rooms[2][37]->addQuestion(q11);

    Question* q12 = new Question;
    q12->changeQuestion("The local gang catches an acquaintance in a loop of crime and blackmail. You...");
    q12->addAnswer("a. It’s really not your problem. It’s his problem for being so stupid");
    q12->addStat("Neutral",20);
    q12->addAnswer("b. Gain the help of the local authorities; you know them well so they'll go easy on your acquaintance in exchange for busting the big fish.");
    q12->addStat("Lawful",10, "Good", 10);
    q12->addAnswer("c. Pretend to be part of that gang and send your new 'flunky' to his next task.");
    q12->addStat("Chaotic",10);
    q12->addAnswer("d. Give the guy some help under the table, but nothing that would attract attention to you");
    q12->addStat("Chaotic", 10, "Evil", 3);
    rooms[2][36]->addQuestion(q12);

}

roomlist::~roomlist()
{
    for (uint i = 0; i <7; i++)
    {
        for (uint j = 0; j < 64; j++)
            delete rooms[i][j];
    }
}
