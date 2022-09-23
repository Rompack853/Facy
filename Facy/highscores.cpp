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

//=========EDIT-INTERNAL-LIST================

/**
 * To Get a specific Score at the specified index
 * @brief Highscores::getElementByID
 * @param i
 * @return Score* score
 */
Score* Highscores::getElementByID(int i){

    return scores.at(i);
}

/**
 * Returns the lenght of the List
 * @brief Highscores::getLength
 * @return int length
 */
int Highscores::getLength(){

    return scores.length();
}

/**
 * Replaces the current object at index i with the specified Object (which is the second parameter)
 * @brief Highscores::replace
 * @param i
 * @param newScore
 */
void Highscores::replace(int i, Score* newScore){
    scores.replace(i, newScore);
}

/**
 * return the index of an Object in the list
 * @brief Highscores::indexOf
 * @param score
 * @return int
 */
int Highscores::indexOf(Score* score){
    return scores.indexOf(score);
}
