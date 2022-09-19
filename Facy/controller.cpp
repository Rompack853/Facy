#include "controller.h"

/**
 * Constructor
 * @brief Controller::Controller
 */
Controller::Controller(){
    //setting up the basic functionality of the Class
    setup();
}

/**
 * Destructor
 * @brief Controller::~Controller
 */
Controller::~Controller(){
    //closing the connection to the Database
    database.closeConnection();
}

/**
 * @brief Controller::setup
 * Basic Setup of Connection and Data that is
 * crutial for the Controller to work
 */
void Controller::setup(){
    qDebug()<<"Database found & Connected: "<<database.connect();
}

/**
 * @brief Controller::addUser
 * @param role
 * @param username
 * @param secret
 * adds the User to the runtime memory and the persistent database
 */
void Controller::addUser(Role role, QString username, QString secret){

    User* user = new User(username, secret);
    users.append(user);

    qDebug() << "Writing " << username << " to Database successful: " << database.addUser(user, role);
}

/**
 * @brief Controller::addGroup
 * @param name
 * @param dirPath
 * @param description
 * adds the Group to the runtime memory and the persistent Database
 */
void Controller::addGroup(QString name, QString dirPath, QString description){

    Group* group = new Group(name, dirPath, description);
    groups.append(group);

    qDebug() << "Writhing " << name << " to Database successful: " << database.addGroup(group);
}

/**
 * @brief Controller::addHighscore
 * @param user
 * @param group
 * @param score
 * adds the Highscore to the runtime memory and the persistent Database
 * !But only if it's score is higher than the previous records
 */
void Controller::addHighscore(User* user, Group* group, int score){

    Score* scoreObj = new Score(user, group, score);

    if( highscores.addHighscore( scoreObj ) ){
        qDebug() << "Writhing new Highscore of " << user->getUsername() << " to Database successful: " << database.addHighscore( scoreObj );  //add new Highscore to the Database
    }//if new highscore has been set
    else{
        qDebug() << "Adding Highscore failed due to existing better scores";
    }//if new highscore hasn't been set

}//addHighscore()
