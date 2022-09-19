#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "database.h"
#include "server.h"

class Controller
{
public:
    Controller();
    ~Controller();

    void addUser(Role role, QString username, QString secret);
    void addGroup(QString name, QString dirPath, QString description);
    void addHighscore(User* user, Group* group, int score);

    void deleteUser(QString usernameToDelete, QString usernameExecuting);
    void deleteGroup(); //TODO
    void deleteHighscore(); //TODO

    //=======NETWORKING=======

    //=======DATABASE=========

    //==========GUI===========


private:
    QList<User*> users;
    QList<Group*> groups;
    Highscores highscores;

    Database database;

    User* getUserByName(QString username);

    void setup();
};

#endif // CONTROLLER_H
