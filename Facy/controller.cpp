#include "controller.h"

Controller::Controller(){
    //setting up the basic functionality of the Class
    setup();
}

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


//Vollstaendig Fertig
void Controller::addUser(Role role, QString username, QString secret){

    User* user = new User(username, secret);

    qDebug() << "Writing " << username << " to Database successful: " << database.addUser(user, role);
}
