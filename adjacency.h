#ifndef ADJACENCY_H
#define ADJACENCY_H
#include "weights.h"

typedef unsigned int uint;

class Adjacency
{
public:
    Adjacency();
    ~Adjacency();

private:
    weights* adjacencytable[7][36][36]; // 7 levels of 36x36 weighted adjacencies for 36 rooms per level
};

#endif // ADJACENCY_H
