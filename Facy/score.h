#ifndef SCORE_H
#define SCORE_H

#include "user.h"
#include "group.h"

class Score
{
public:
    Score(User* user, Group* group, int score=0);

    User* getUser();
    Group* getGroup();
    int getScore();

private:
    User* user;
    Group* group;
    int score;
};

#endif // SCORE_H
