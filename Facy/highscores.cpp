#include "highscores.h"

Highscores::Highscores()
{

}

/**
 * @brief Highscores::addHighscore
 * @param score
 * @return a boolean that indicates if the score has been added successfully
 * false - if a higher score exists in the same group
 * true - if the socre is higher than previous ones or the first score in the group
 */
bool Highscores::addHighscore(Score* score){

    for(Score* s: scores){
        if(s->getGroup() == score->getGroup()){
            //if new score is higher: save the new Score
            if(s->getScore() < score->getScore()){
                deleteScore(s); //remove the old highscore
                scores.append(score); //add the new highscore
                return true;
            }
            //if old score is higher or the same: return false
            else {
                return false;
            }
        }//if the scores have been achived in the same group
    }//for s

    //if no entry in this group was found till
    scores.append(score);
    return true;
}//addHighscore()

/**
 * @brief Highscores::deleteScore
 * @param score
 * removes the score for the List of highscores
 */
void Highscores::deleteScore(Score* score){

    scores.removeAll(score);
}
