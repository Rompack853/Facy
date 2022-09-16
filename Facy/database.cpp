#include "database.h"
#include "QDebug"

Database::Database()
{

}

//Vollstaendig Fertig
bool Database::connect(){
    QString dbPfad = QApplication::applicationDirPath() + "/../datenbank.sqlite";
    qDebug()<<"Database path sepcified: "<<dbPfad;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPfad);
    return db.open();
}

//Vollstaendig Fertig
void Database::closeConnection(){
    db.close();
}

//Vollstaendig Fertig
bool Database::execute(QString sqlQuery){

    qDebug()<<sqlQuery;

    bool success = false;

    if(db.isOpen()){

        QSqlQuery qry;

        //SQL-Befehl ausführen lassen
        success = qry.exec(sqlQuery);

    }//if datenbank ist geoeffnet

    return success;
}

bool Database::addUser(User* user, Role role){

    QString sqlBefehl;

    if(role == Role::USER)
        sqlBefehl = buildAddUserQuery(user);
    else
        sqlBefehl = buildAddAdminQuery(user);

    return execute(sqlBefehl);
}

QString Database::buildAddAdminQuery(User* user){

    QString sqlBefehl = ""; //TODO

    return sqlBefehl;
}

QString Database::buildAddUserQuery(User* user){

    QString sqlBefehl = ""; //TODO

    return sqlBefehl;
}
