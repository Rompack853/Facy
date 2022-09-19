#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "score.h"

class Highscores
{
public:
    //Constructor
    Highscores();

    //Add entry
    bool addHighscore(Score* score);
    //delete entry
    void deleteScore(Score* score);
    //get entry
    //TODO

private:
    QList<Score*> scores;
};

#endif // HIGHSCORES_H
