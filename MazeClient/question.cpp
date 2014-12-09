#include "question.h"

Question::Question()
{

}

Question::Question(const Question &other)
{
    copy(other);
}

Question::~Question()
{
    nukem();
}

Question &Question::operator =(const Question &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
}

void Question::addAnswer(QString answer)
{
    questionanswers.push_back(answer);
}

void Question::addStat(stats *newStat)
{
    questionstats.push_back(newStat);
}

void Question::changeQuestion(QString q)
{
    theQuestion = q;
}

void Question::copy(const Question &other)
{
    this->theQuestion = other.theQuestion;
    for (int i = 0; i < other.questionanswers.size(); i++)
        this->questionanswers.push_back(other.questionanswers[i]);
    for (int i = 0; i < other.questionstats.size(); i++)
        this->questionstats.push_back(other.questionstats[i]);

}

void Question::nukem()
{
    questionstats.clear();
    questionanswers.clear();
    theQuestion.clear();

}
