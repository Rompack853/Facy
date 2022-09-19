#include "database.h"
#include "QDebug"

/**
 * Constructor
 * @brief Database::Database
 */
Database::Database()
{

}

//Vollstaendig Fertig
/**
 * Tries to build a connection to the Database
 * @brief Database::connect
 * @return true - if successful
 * false - if no connection could be established
 */
bool Database::connect(){
    QString dbPfad = QApplication::applicationDirPath() + "/../datenbank.sqlite";
    qDebug()<<"Database path sepcified: "<<dbPfad;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPfad);
    return db.open();
}

/*
bool Database::connect(){
    char* zErrMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if( rc ) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return(0);
    } else {
       fprintf(stderr, "Opened database successfully\n");
    }
    return db.;
}*/

//Vollstaendig Fertig
/**
 * Closes the connection to the Databases propperly
 * @brief Database::closeConnection
 */
void Database::closeConnection(){
    db.close();
}

/*
void Database::closeConnection(){
    sqlite3_close(db);
}*/

//Vollstaendig Fertig
/**
 * Executes the
 * @brief Database::execute
 * @param sqlQuery
 * @return true - if successful
 * false - if not successful
 */
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

//===================ADD-METHODS===================

//Vollstaendig Fertig
/**
 * Adds a User (or Admin) to the Database
 * !Take care and choose the correct Role!
 * @brief Database::addUser
 * @param user
 * @param role
 * @return true - if successful
 */
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

/**
 * Adds a Group to the Database
 * @brief Database::addGroup
 * @param group
 * @return true - if successful
 */
bool Database::addGroup(Group* group){

    QString sqlBefehl = "INSERT INTO Group (name, dir_path, description) "
                        "VALUES ('" + group->getName() + "', '" + group->getDirPath() + "', '" + group->getDescription() + "');";

    return execute(sqlBefehl);
}

/**
 * @brief Database::addHighscore
 * @param score
 * @return true - if successful
 */
bool Database::addHighscore(Score* score){

    QString sqlBefehl = "INSERT INTO Scoreboard (id_user, id_group, highscore) "
                        "VALUES ( (SELECT id"
                                  "FROM User"
                                  "WHERE username = '"+ score->getUser()->getUsername() + "'), (SELECT id"
                                                                                               "FROM Group"
                                                                                              "WHERE name = '" + score->getGroup()->getName() + "'), '" + score->getScore() + "');";
    return execute(sqlBefehl);
}

//===================GET-METHODS===================





//===================BUILD-QUERY-METHODS===================

//Vollstaendig Fertig
/**
 * Builds a SQLQuery for adding an Admin to the Database
 * @brief Database::buildAddAdminQuery
 * @param user
 * @return SQLQuery as String
 */
QString Database::buildAddAdminQuery(User* user){

    //Traegt in die Tabelle Admin die ID des Users ein.

    QString sqlBefehl = "INSERT INTO Admin (id) "
                        "VALUES ((SELECT id "
                                  "FROM User "
                                  "WHERE username = '" +user->getUsername()+ "'));";
    return sqlBefehl;
}


//Vollstaendig Fertig
/**
 * Builds a SQLQuery for adding an User to the Database
 * @brief Database::buildAddUserQuery
 * @param user
 * @return SQLQuery as String
 */
QString Database::buildAddUserQuery(User* user){

    //Tragat in die Tabelle des Users die Values für den Username und das Passwort ein.
    QString sqlBefehl = "INSERT INTO User (username, secret) "
                        "VALUES ('" + user->getUsername() + "', '" + user->getSecret() + "');";
    return sqlBefehl;
}
