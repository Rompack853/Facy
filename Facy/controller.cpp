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
 * Crutial for the Controller to work
 * @brief Controller::setup
 * Basic Setup of Connection and Data that is
 */
void Controller::setup(){
    qDebug()<<"Database found & Connected: "<<database.connect();
    loadUsers();
    loadGroups();
    loadHighscores();
}

//==============ADD-DATA================

/**
 * Adds the User to the runtime memory and the persistent database
 * @brief Controller::addUser
 * @param role
 * @param username
 * @param secret
 */
void Controller::addUser(Role role, QString username, QString secret){

    User* user = new User(username, secret);
    users.append(user);

    qDebug() << "Writing " << username << " to Database successful: " << database.addUser(user, role);
}

/**
 * Adds the Group to the runtime memory and the persistent Database
 * @brief Controller::addGroup
 * @param name
 * @param dirPath
 * @param description
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
 * Adds the Highscore to the runtime memory and the persistent Database
 * !But only if it's score is higher than the previous records
 * @brief Controller::addHighscore
 * @param user
 * @param group
 * @param score
 */
void Controller::addHighscore(QString username, QString groupname, int score){

    User* user = getUserByName(username);
    Group* group = getGroupByName(groupname);
    Score* scoreObj = new Score(user, group, score);

    if(user != nullptr &&
       group != nullptr &&
       score > 0){
        if( highscores->addHighscore( scoreObj ) ){
            qDebug() << "Writhing new Highscore of " << user->getUsername() << " to Database successful: " << database.addHighscore( scoreObj );  //add new Highscore to the Database
        }//if new highscore has been reached & set
        else{
            qDebug() << "Adding Highscore failed due to existing better scores";
        }//if new highscore hasn't been reached & set
    }//if user & group exist AND score is bigger than 0
    else{
        qDebug()<<"addHighscore() canceled due to incorrect data";
    }
}//addHighscore()

//============GET-DATA============

/**
 * returns the User object identified by the username
 * @brief Controller::getUserByName
 * @param username
 * @return
 */
User* Controller::getUserByName(QString username){

    loadUser(username); //tries to loadUser from DB (if it already got loaded the software notices it and stops automaticly)

    for(User* u: users){
       if(u->getUsername()==username){
            return u;
       }//if
    }//for u
    return nullptr;
}//getUserByName()

Group* Controller::getGroupByName(QString name){

    for(Group* g: groups){
        if(g->getName() == name){
            return g;
        }//if names match
    }//for g
    return nullptr;
}//getGroupByName()

//============LOAD-DATA===========

/**
 * Should only be executed one time in the !beginning of the programm
 * due to the circumstance that this method doesn't check for double entries
 * in list 'users'. If you need that check use getUserByName(QString username) or loadUser(QString username)
 * @brief Controller::loadUsers
 */
void Controller::loadUsers(){
    users = database.loadAllUsers();
    qDebug() << "lol";
}//loadUsers

/**
 * Loads a User spezified by the username parameter from the Database
 * @brief Controller::loadUser
 * @param username
 * @return bool if the User has been found & loaded (false if user already loaded OR not found)
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
        User* user = database.loadUser(username);
        if(user != nullptr){
            users.append(user);
            print("User/Admin loaded");
            return true;
        }//user exists
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

bool Controller::loadHighscores(){

    highscores = database.loadHighscores();
    //iterate over highscores entrys and replace the groupDummies and userDummies with the real objects
    //IDEA: Create Method in highscores where you give the 'users' and 'groups' Lists and do it
    //if there is no way iterating over the score from the controller

    for(int i=0; i<highscores->getLength(); i++){
        for(User* u: users){
            if( u->getUsername() == highscores->getElementByID(i)->getUser()->getUsername() ){
                for(Group* g: groups){
                    if( g->getName() == highscores->getElementByID(i)->getGroup()->getName() ){
                        int points = highscores->getElementByID(i)->getScore();
                        delete(highscores->getElementByID(i));
                        highscores->replace(i, new Score(u, g, points));
                    }//if groupName == score.groupName
                }//for g in groups
            }//if users.userName == score.userName
        }//for u in users
    }//for int i

    print("Highscores loaded");
    return false;
}

//===============================
//===========SECURITY============
//===============================

bool checkUserCredentials(QString username, QString secret){
    //TODO
    return false;
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
