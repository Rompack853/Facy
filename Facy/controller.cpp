#include "controller.h"
#include "qlabel.h"

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

    /* test for image-load: working!
    for(Group* g: groups){
        for(QImage* i: Filesystem::getInstance()->loadImages(g)){
            qDebug()<<QString::number(i->width())+"px";
        }//for
    }//for */

}

//==============ADD-DATA================

/**
 * Adds the User to the runtime memory and the persistent database
 * @brief Controller::addUser
 * @param role
 * @param username
 * @param secret
 */
bool Controller::addUser(Role role, QString username, QString secret){

    if(getUserByName(username)!=nullptr){
        return false;
    }

    User* user;

    if(role == Role::USER){
        user = new User(username, secret);
    } else {
        user = new Admin(username, secret);
    }
    users.append(user);
    qDebug() << "Writing " << username << " to Database successful: " << database.addUser(user, role);
    return true;
}

/**
 * Adds the Group to the runtime memory and the persistent Database
 * @brief Controller::addGroup
 * @param name
 * @param dirPath
 * @param description
 */
bool Controller::addGroup(QString name, QString description){

    if(getGroupByName(name)!=nullptr){
        return false;
    }

    bool success = false;

    Group* group = new Group(name, description);
    groups.append(group);

    success = database.addGroup(group);

    qDebug() << "Writing " << name << " to Database successful: " << success;

    if(success){
        if(Filesystem::getInstance()->createNewGroupDir(name))
            return true;
    }//if adding Group to Database was successful -> create a directory for the groups images
    return false;
}

/**
 * Adds the Highscore to the runtime memory and the persistent Database
 * !But only if it's score is higher than the previous records
 * @brief Controller::addHighscore
 * @param user
 * @param group
 * @param score
 */
bool Controller::addHighscore(QString username, QString groupname, int score){

    User* user = getUserByName(username);
    Group* group = getGroupByName(groupname);
    Score* scoreObj = new Score(user, group, score);

    if(user != nullptr &&
       group != nullptr &&
       score > 0){
        if( highscores->addHighscore( scoreObj ) ){
            return database.addHighscore( scoreObj );  //add new Highscore to the Database
        }//if new highscore has been reached & set
        else{
            qDebug() << "Adding Highscore failed due to existing better scores";
        }//if new highscore hasn't been reached & set
    }//if user & group exist AND score is bigger than 0
    else{
        qDebug()<<"addHighscore() canceled due to incorrect data";
    }
    return false;
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
       if(u->getUsername().toLower()==username.toLower()){
            return u;
       }//if
    }//for u
    return nullptr;
}//getUserByName()

/**
 * Returns a group-object specified by the name
 * @brief Controller::getGroupByName
 * @param name
 * @return
 */
Group* Controller::getGroupByName(QString name){

    for(Group* g: groups){
        if(g->getName().toLower() == name.toLower()){
            return g;
        }//if names match
    }//for g
    return nullptr;
}//getGroupByName()

/**
 * returns all group-objects
 * @brief Controller::getGroups
 * @return
 */
QList<Group*> Controller::getGroups(){

    return groups;
}

/**
 * returns all user-objects
 * @brief Controller::getUsers
 * @return
 */
QList<User*> Controller::getUsers(){

    return users;
}

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

/**
 * Loads the Highscores form the Database
 * @brief Controller::loadHighscores
 * @return
 */
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
bool Controller::isAdmin(User* user){
    //Admin* admin = dynamic_cast<Admin*>(user);
    return true;
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
