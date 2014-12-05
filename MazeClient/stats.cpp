#include "stats.h"

stats::stats(string stat_name, double val)
{
    statname = stat_name;
    value = val; // can even be negative
}

stats::stats(const stats &other)
{
    copy(other);
}

stats::~stats()
{
    nukem();
}

string stats::getname() const
{
    return statname;
}

double stats::getvalue() const
{
    return value;
}

void stats::copy(const stats &other)
{
    statname = other.getname();
    value = other.getvalue();
}

void stats::nukem()
{
    // nothing
}

