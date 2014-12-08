#ifndef ADJACENCY_H
#define ADJACENCY_H
#include "weights.h"

typedef unsigned int uint;

class Adjacency
{
public:
    Adjacency();
    ~Adjacency();
    weights *getWeight(int room_num, int next_room, int current_level);

protected:
private:
    weights* adjacencytable[7][64][64]; // 7 levels of 36x36 weighted adjacencies for 36 rooms per level
};

#endif // ADJACENCY_H
