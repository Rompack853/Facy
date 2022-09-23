#ifndef DATABASE_H
#define DATABASE_H
#include <QWidget>
#include <QtSql>
#include <QApplication>
#include "admin.h"
#include "group.h"
#include "score.h"
#include "highscores.h"
#include "Role.h"
#include <sqlite3.h>

class Database : public QObject
{
public:
    Database();                             //FERTIG
    //===========CONNECTION==========
    bool connect();                         //FERTIG
    void closeConnection();                 //FERTIG
    //========DATEN SCHREIBEN========
    //Also Admins are processed here
    bool addUser(User* user, Role role);    //FERTIG
    bool addHighscore(Score* score);        //FERTIG
    bool addGroup(Group* group);            //FERTIG
    //===========DATEN LESEN=========
    QList<User*> loadAllUsers();
    User* loadUser(QString username);       //FERTIG
    QList<Group*> loadGroups();             //FERTIG
    Highscores* loadHighscores();           //FERTIG

private:

    //==========LOGIC===============
    QString buildAddAdminQuery(User* user); //FERTIG
    QString buildAddUserQuery(User* user);  //FERTIG

    bool execute(QString query);            //FERTIG
    void printError(QSqlQuery qry);         //FERTIG

    //==========Attributes==========
    QSqlDatabase db;
    //sqlite3* db;

};

#endif // DATABASE_H
