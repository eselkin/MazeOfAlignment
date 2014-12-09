#ifndef QUESTION_H
#define QUESTION_H
#include <QString>
#include <QVector>
#include "stats.h"

struct Question
{
    QString theQuestion;
    QVector<QString> questionanswers;
    QVector<stats*> questionstats; // always pointers to give to the player and remove from here.

    Question();
    Question(const Question& other);
    ~Question();
    Question& operator =(const Question& other);
    void addAnswer(QString answer);
    void addStat(stats* newStat);
    void changeQuestion(QString q);
    void copy(const Question& other);
    void nukem();

};

#endif // QUESTION_H
