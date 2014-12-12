#ifndef QUESTION_H
#define QUESTION_H
#include <QString>
#include <QVector>
#include <utility>
#include <cstdlib>
#include <QString>

using namespace std;
typedef pair<QString, int> mQPair;

struct Question
{
    QString theQuestion;
    QVector<QString> questionanswers;
    QVector< pair<mQPair,mQPair> > questionstats; // always pointers to give to the player and remove from here.

    Question();
    Question(const Question& other);
    ~Question();
    Question& operator =(const Question& other);
    void addAnswer(QString answer);
    void addStat(pair<mQPair, mQPair>);
    void addStat(QString stat_i, int val_i, QString stat_ii, int val_ii);
    void changeQuestion(QString q);
    void copy(const Question& other);
    void nukem();

};

#endif // QUESTION_H
