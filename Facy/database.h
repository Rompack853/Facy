#ifndef DATABASE_H
#define DATABASE_H
#include <QWidget>
#include <QtSql>
#include <QApplication>
#include "admin.h"
#include "Role.h"

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
    bool addUser(User* user, Role role);

    //===========DATEN LESEN=========

private:

    //Methods
    bool execute(QString query);

    //==========LOGIC===============
    QString buildAddAdminQuery(User* user);
    QString buildAddUserQuery(User* user);

    //==============================

    //Attributes
    QSqlDatabase db;
};

#endif // DATABASE_H
