#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "database.h"
#include "filesystem.h"

class Controller : public QObject
{
public:
    Controller();
    ~Controller();

    //===========ADD-DATA================
    bool addUser(Role role, QString username, QString secret);          //FERTIG
    bool addGroup(QString name, QString description);  //FERTIG
    bool addHighscore(QString username, QString groupname, int score);  //FERTIG

    //=========GET-DATA=================
    User* getUserByName(QString username); //FERTIG
    Group* getGroupByName(QString name); //FERTIG
    QList<Group*> getGroups(); //FERTIG
    QList<User*> getUsers(); //FERTIG

    //=========DELETE-DATA===============
    void deleteUser(QString usernameToDelete, QString usernameExecuting); //IMPELMENT IF NEEDED
    void deleteGroup();                                                   //IMPELMENT IF NEEDED
    void deleteHighscore();                                               //IMPELMENT IF NEEDED

    //=========SECURITY=======
    bool isAdmin(User* user);

    //=======NETWORKING=======

    //=======DATABASE=========

    //==========GUI===========
private:
    //==========ATTRIBUTES========
    QList<User*> users;
    QList<Group*> groups;
    Highscores* highscores;
    Database database;
    //==========FUNCTIONS=========
    void setup();
    void print(QString message); //FERTIG
    //========LOAD-FROM-DATABASE=========
    void loadUsers();                   //FERTIG
    bool loadUser(QString username);    //FERTIG
    void loadGroups();                  //FERTIG
    bool loadHighscores();              //FERTIG
};

#endif // CONTROLLER_H
