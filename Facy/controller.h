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
    void addUser(Role role, QString username, QString secret);          //FERTIG
    void addGroup(QString name, QString dirPath, QString description);  //FERTIG
    void addHighscore(QString username, QString groupname, int score);  //FERTIG

    //========LOAD-FROM-DATABASE=========
    void loadUsers();                   //FERTIG
    bool loadUser(QString username);    //FERTIG
    void loadGroups();                  //FERTIG
    bool loadHighscores();              //FERTIG

    //=========DELETE-DATA===============)
    void deleteUser(QString usernameToDelete, QString usernameExecuting); //IMPELMENT IF NEEDED
    void deleteGroup();                                                   //IMPELMENT IF NEEDED
    void deleteHighscore();                                               //IMPELMENT IF NEEDED

    //=========SECURITY=======

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

    User* getUserByName(QString username); //TODO Test
    Group* getGroupByName(QString name); //TODO Test
};

#endif // CONTROLLER_H
