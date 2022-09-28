#include "user.h"

//#########################
//VOLLSTAENDIG FERTIG
//#########################

User::User(QString username, QString secret)
{
    this->username = username;
    this->secret = secret;
}

void User::setUsername(QString newUsername){

    this->username = newUsername;
}

void User::setSecret(QString newSecret){

    this->secret = newSecret;
}

QString User::getUsername(){

    return this->username;
}

QString User::getSecret(){
    //Maybe unencrypt here
    return this->secret;
}

bool User::validateCredentials(QString tryUsername, QString trySecret){
    return (tryUsername == this->username && trySecret == this->secret);
}
