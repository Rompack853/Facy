#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "database.h"

class Controller
{
public:
    Controller();

    void addUser(Role role, QString username, QString secret);
    void deleteUser(QString usernameToDelete, QString usernameExecuting);

    //=======NETWORKING=======

    //=======DATABASE=========

    //==========GUI===========


private:
    QList<User*> user;
    Database database;

    User* getUserByName(QString username);

    void setup();
};

#endif // CONTROLLER_H
