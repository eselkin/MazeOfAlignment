#include "room.h"

room::room()
{
}

room::room(const room &other)
{
    copy(other);
}

room &room::operator=(const room &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

room::~room()
{
    uint sizeofroom = avail_contents.size();
    uint numattributes = stat_alterations.size();
    avail_contents.clear();
    stat_alterations.clear();
}

vector<pair< pair<QString, int>, pair<QString, int> > > room::getStats()
{
    return stat_alterations;
}

vector<items *> room::getItems()
{
    return avail_contents;
}

vector<Question *> room::getQuestions()
{
    return room_questions;
}

vector<pair< pair<QString, int>, pair<QString, int> > > room::getStats() const
{
    return stat_alterations;
}

vector<items *> room::getItems() const
{
    return avail_contents;
}

vector<Question *> room::getQuestions() const
{
    return room_questions;
}

void room::addItem(items *newitem)
{
    avail_contents.push_back(newitem);
}

void room::addQuestion(Question *newQuestion)
{
    room_questions.push_back(newQuestion);
}

void room::delQuestion(int num)
{
    int i = 0;
    vector<Question *>::iterator it;
    for (it = room_questions.begin(); i < num; it++)
    {
        i++;
        room_questions.erase(it);
    }
}

items *room::removeItem(int item_num)
{
    items* temp = avail_contents[item_num];
    vector<items*>::iterator vIT = avail_contents.begin();
    int i = 0;
    for (; i < item_num && vIT != avail_contents.end(); vIT++, i++);
    avail_contents.erase(vIT); // remove it from the contents of the room
    return temp;
}

void room::copy(const room &other)
{
    uint other_size = other.getItems().size();
    for (uint i = 0; i < other_size; i++)
        avail_contents.push_back(new items(*other.getItems()[i]));
    other_size = other.getStats().size();
    for (uint i = 0; i < other_size; i++)
        stat_alterations.push_back(other.getStats()[i]);
}

void room::nukem()
{

}
