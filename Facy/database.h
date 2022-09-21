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

class Database
{
public:
    //constuctor
    Database(); //FERTIG

    //===========CONNECTION==========
    //Methods
    bool connect(); //FERTIG
    void closeConnection(); //FERTIG

    //========DATEN SCHREIBEN========
    //Also Admins are processed here
    bool addUser(User* user, Role role); //FERTIG
    bool addHighscore(Score* score); //TODO überlege ob (DELETE && INSERT INTO) oder UPDATE genutzt werden soll um neue Werte einzutragen/alte zu bearbeiten
    bool addGroup(Group* group); //TODO Testen of funktionsfähig

    //===========DATEN LESEN=========
    User* loadUser(QString username); //FERTIG
    QList<Group*> loadGroups(); //TODO
    Highscores* loadHighscores(); //TODO

private:

    //Methods
    bool execute(QString query); //FERTIG
    void printError(QSqlQuery qry); //FERTIG
    //==========LOGIC===============
    QString buildAddAdminQuery(User* user); //FERTIG
    QString buildAddUserQuery(User* user); //FERTIG

    //==============================

    //Attributes
    QSqlDatabase db;
    //sqlite3* db;

};

#endif // DATABASE_H
