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

    //======Edit-internal-List==========
    Score* getElementByID(int i);
    int getLength();
    void replace(int index, Score* newScore);
    int indexOf(Score* score);

private:
    QList<Score*> scores;
};

#endif // HIGHSCORES_H
