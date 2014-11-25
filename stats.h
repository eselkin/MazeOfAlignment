#ifndef STATS_H
#define STATS_H
#include <string>

using namespace std;

class stats
{

public:
    stats(string stat_name, double val);
    ~stats();
    string getname() const;
    double getvalue() const;

private:
    copy(const stats &other);
    string statname;
    double value;
};

stats::stats(string stat_name, double val)
{
    statname = stat_name;
    value = val; // can even be negative
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

stats::copy(const stats &other)
{
    statname = other.getname();
    value = other.getvalue();
}
#endif // STATS_H
