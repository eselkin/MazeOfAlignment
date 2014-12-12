#ifndef QUESTION_H
#define QUESTION_H
#include <QString>
#include <QVector>

struct Question
{
    QString theQuestion;
    QVector<QString> questionanswers;
    QVector<pair<pair<QString, int>, pair<QString, int> > > questionstats; // always pointers to give to the player and remove from here.

    Question();
    Question(const Question& other);
    ~Question();
    Question& operator =(const Question& other);
    void addAnswer(QString answer);
    void addStat(pair<pair<QString, int>, pair<QString, int> > );
    void changeQuestion(QString q);
    void copy(const Question& other);
    void nukem();

};

#endif // QUESTION_H
