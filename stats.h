#ifndef STATS_H
#define STATS_H
#include <string>

using namespace std;

class stats
{

public:
    stats(string stat_name="", double val=0.0);

    ~stats();
    string getname() const;
    double getvalue() const;

private:
    void copy(const stats &other);
    void nukem();
    string statname;
    double value;
};

#endif // STATS_H
