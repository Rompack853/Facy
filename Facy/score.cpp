#include "score.h"

//#########################
//VOLLSTAENDIG FERTIG
//#########################

Score::Score(User* user, Group* group, int score=0)
{
    this->user = user;
    this->group = group;
    this->score = score;
}

User* Score::getUser(){
    return this->user;
}

Group* Score::getGroup(){
    return this->group;
}

int Score::getScore(){
    return this->score;
}
