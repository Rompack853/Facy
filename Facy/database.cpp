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

//Vollstaendig Fertig
bool Database::addUser(User* user, Role role){

    QString sqlBefehl = "";
    bool sqlExecution1 = false;
    bool sqlExecution2 = false;

    if(role == Role::ADMIN){
        sqlBefehl = buildAddUserQuery(user);
        sqlExecution1 = execute(sqlBefehl);
        sqlBefehl = buildAddAdminQuery(user);
        sqlExecution2 = execute(sqlBefehl);

        //wenn der Admin erolgreich in die Datenbank geschrieben wurden,
        //soll true return werden
        return (sqlExecution2 && sqlExecution1) == true;
    }//if
    else{
        sqlBefehl = buildAddUserQuery(user);
        //wenn der User erolgreich in die Datenbank geschrieben wurden,
        //soll true return werden
        return execute(sqlBefehl);
    }//else
}//addUser();


//Vollstaendig Fertig
QString Database::buildAddAdminQuery(User* user){

    //Traegt in die Tabelle Admin die ID des Users ein.

    QString sqlBefehl = "INSERT INTO Admin (id) "
                        "VALUES ((SELECT id "
                                  "FROM User "
                                  "WHERE username = '" +user->getUsername()+ "'));"; //TODO
    return sqlBefehl;
}


//Vollstaendig Fertig
QString Database::buildAddUserQuery(User* user){

    //Tragat in die Tabelle des Users die Values für den Username und das Passwort ein.
    QString sqlBefehl = "INSERT INTO User (username, secret) "
                        "VALUES ('" + user->getUsername() + "', '" + user->getSecret() + "');"; //TODO
    return sqlBefehl;
}
