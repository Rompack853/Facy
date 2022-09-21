#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "database.h"
#include "server.h"
#include "filesystem.h"

class Controller
{
public:
    Controller();
    ~Controller();

    //===========ADD-DATA================
    void addUser(Role role, QString username, QString secret); //FERTIG
    void addGroup(QString name, QString dirPath, QString description);
    void addHighscore(User* user, Group* group, int score);

    //========LOAD-FROM-DATABASE=========
    bool loadUser(QString username); //FERTIG
    void loadGroups();
    bool loadHighscores();

    //=========DELETE-DATA===============)
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

    User* getUserByName(QString username); //TODO Test

    void print(QString message); //Fertig


    void setup();
};

#endif // CONTROLLER_H
