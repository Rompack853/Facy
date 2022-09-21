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

//==============ADD-DATA================

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

    bool success = false;

    Group* group = new Group(name, dirPath, description);
    groups.append(group);

    success = database.addGroup(group);

    qDebug() << "Writing " << name << " to Database successful: " << success;

    if(success){
        Filesystem::getInstance()->createNewGroupDir(name);
    }//if adding Group to Database was successful -> create a directory for the groups images
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

//============GET-DATA============

User* Controller::getUserByName(QString username){

    //TODO
    return nullptr;
}

//============LOAD-DATA===========

/**
 * Loads a User spezified by the username parameter from the Database
 * @brief Controller::loadUser
 * @param username
 * @return bool if the User has been found & loaded
 */
bool Controller::loadUser(QString username){

    bool userAlreadyLoaded = false;

    for(User* user: users){
        if(user->getUsername() == username){
            userAlreadyLoaded = true;
            print("User already exists.");
            break;
        }//if
    }//for

    if(!userAlreadyLoaded){
        users.append(database.loadUser(username));
        print("User/Admin loaded");
        return true;
    }//if user not loaded yet
    return false;
}//loadUser()

/**
 * Calling this Methods overrides the current state of the Group-List with the state of the Database
 * @brief Controller::loadGroups
 * @return
 */
void Controller::loadGroups(){

    //TODO maybe outsource the returned list of groups in a temporary list and compare the entrys to the current list
    //just load those that are new
    groups = database.loadGroups();
    print("Groups loaded");
}

//============More================

/**
 * Prints a specified message in the Console
 * @brief Controller::print
 * @param message
 */
void Controller::print(QString message){
    qDebug() << message;
}
