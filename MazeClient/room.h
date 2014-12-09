#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include "items.h"
#include "question.h"

typedef unsigned int uint;

class room
{
public:
    room();
    room(const room &other);
    room& operator=(const room &other);
    ~room();

    vector<stats*> getStats();
    vector<items*> getItems();
    vector<Question*> getQuestions(); // non const
    vector<stats*> getStats() const;
    vector<items*> getItems() const;
    vector<Question*> getQuestions() const; // non const
    void addItem(items *newitem);
    void addQuestion(Question *newQuestion);
    void delQuestion(int num);
    items* removeItem(int item_num);

private:
    void copy(const room &other);
    void nukem();
    vector<items*> avail_contents; // pointers so that when someone takes them, they can be transferred in just one memory space!
    vector<stats*> stat_alterations;
    vector<Question*> room_questions;
};

#endif // ROOM_H
