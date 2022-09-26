#include "connection.h"

Connection::Connection(QString id, QTcpSocket* socket)
{
    this->id = id;
    this->socket = socket;
}

//=====GETTER=========

QString Connection::getID(){
    return id;
}

bool Connection::isLoggedIn(){
    return loggedIn;
}

QTcpSocket* Connection::getSocket(){
    return socket;
}

//=====SETTER=========

void Connection::setLoggedIn(bool loggedIn){
    this->loggedIn = loggedIn;
}

//=====MORE===========

QString Connection::generateRandomID(){

    return QString::number(QRandomGenerator64::global()->generate(), 10);
}
