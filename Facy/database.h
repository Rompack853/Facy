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
    Database();

    //===========CONNECTION==========
    //Methods
    bool connect();
    void closeConnection();

    //========DATEN SCHREIBEN========
    //Also Admins are processed here
    bool addUser(User* user, Role role); //FERTIG
    bool addHighscore(Score* score); //TODO überlege ob (DELETE && INSERT INTO) oder UPDATE genutzt werden soll um neue Werte einzutragen/alte zu bearbeiten
    bool addGroup(Group* group); //TODO Testen of funktionsfähig

    //===========DATEN LESEN=========
    QList<User*> loadUsers(); //TODO
    QList<Group*> loadGroups(); //TODO
    Highscores loadHighscores(); //TODO

private:

    //Methods
    bool execute(QString query);

    //==========LOGIC===============
    QString buildAddAdminQuery(User* user);
    QString buildAddUserQuery(User* user);

    //==============================

    //Attributes
    QSqlDatabase db;
    //sqlite3* db;

};

#endif // DATABASE_H
