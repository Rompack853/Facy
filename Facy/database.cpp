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

    QString sqlBefehl = "INSERT INTO Stereotype (name, dir_path, description) "
                        "VALUES ('" + group->getName() + "', '" + group->getDirPath() + "', '" + group->getDescription() + "');";

    return execute(sqlBefehl);
}

/**
 * @brief Database::addHighscore
 * @param score
 * @return true - if successful
 */
bool Database::addHighscore(Score* score){

    QString sqlBefehl = "INSERT INTO Scoreboard (id_user, id_stereotype, highscore) "
                        "VALUES ( (SELECT id "
                                  "FROM User "
                                  "WHERE username = '"+ score->getUser()->getUsername() + "'), (SELECT id "
                                                                                               "FROM Stereotype "
                                                                                               "WHERE name = '" + score->getGroup()->getName() + "'), " + QString::number(score->getScore()) + ");";
    return execute(sqlBefehl);
}

//===================GET-METHODS===================

QList<User*> Database::loadAllUsers(){

    bool success = false;
    User* user = nullptr;
    QList<User*> users;
    QString username = "";
    QString secret = "";
    QString id = "";
    QSqlQuery qry;
    QSqlQuery qry2;

    QString sqlBefehl = "SELECT id, username, secret "
                        "FROM User";

    success = qry.exec(sqlBefehl);

    qDebug() << "Load AllUsers query correct: " << success << "\nSQLQuery:" << sqlBefehl;

    if (success){
        success = qry.first(); //auf erste Zeile springen
        while(success){
            id = qry.value(0).toString();
            username = qry.value(1).toString();
            secret = qry.value(2).toString();

            user = new User(username, secret);

            sqlBefehl = "SELECT * "
                        "FROM Admin "
                        "WHERE id = " + id;

            qDebug() << "\nSQLQuery:" << sqlBefehl;

            success = qry2.exec(sqlBefehl);
            if(success){
                qDebug() << "Load Admin query correct: " << success;
                success = qry2.first();
                if(success){
                    qDebug() << "Load Admin successful: " << success;
                    user = new Admin(username, secret);
                }//if finding entry successful
            }//if query execution successful
            users.append(user);
            success = qry.next();
        }//while success
    }//if finding user successful

    if(user == nullptr){
        printError(qry);
    }//wenn kein User gefunden wurde wird der letzt Fehler in der Konsole ausgegeben

    return users;
}

//Vollstaendig fertig
/**
 * Loads a user from the Database
 * @brief Database::loadUser
 * @param username
 * @return
 */
User* Database::loadUser(QString username){

    bool success = false;
    User* user = nullptr;
    QString secret = "";
    QString id = "";
    QSqlQuery qry;

    QString sqlBefehl = "SELECT id, username, secret "
                        "FROM User "
                        "WHERE username = '" + username + "'";

    success = qry.exec(sqlBefehl);

    qDebug() << "Load User query correct: " << success << "\nSQLQuery:" << sqlBefehl;

    if (success){
        success = qry.first(); //auf erste Zeile springen
        if(success){
            qDebug() << "Load User successful: " << success;
            id = qry.value(0).toString();
            username = qry.value(1).toString();
            secret = qry.value(2).toString();

            user = new User(username, secret);

            sqlBefehl = "SELECT * "
                        "FROM Admin "
                        "WHERE id = " + id;

            qDebug() << "\nSQLQuery:" << sqlBefehl;

            success = qry.exec(sqlBefehl);
            if(success){
                qDebug() << "Load Admin query correct: " << success;
                success = qry.first();
                if(success){
                    qDebug() << "Load Admin successful: " << success;
                    user = new Admin(username, secret);
                }//if finding entry successful
            }//if query execution successful
        }//if success
    }//if finding user successful

    if(user == nullptr){
        printError(qry);
    }//wenn kein User gefunden wurde wird der letzt Fehler in der Konsole ausgegeben

    return user;
}//loadUser()

/**
 * Loads all Groups from the Database
 * @brief Database::loadGroups
 * @return
 */
QList<Group*> Database::loadGroups(){

    Group* group = nullptr; //cache for all group objects
    QString name = "";
    QString description = "";
    QString dirPath = "";
    QList<Group*> groups; //Final List of groups that gets returnt in the end

    bool success = false;
    QSqlQuery qry;
    QString sqlBefehl = "SELECT name, description, dir_path "
                        "FROM Stereotype;";

    qry.exec(sqlBefehl); //execute SQLStatement
    success = qry.first(); //get first Returned value
    while (success) {
        name = qry.value(0).toString();         //loads the groups name
        description = qry.value(1).toString();  //loads the groups description
        dirPath = qry.value(2).toString();      //loads the groups directory Path (more information in the Group class)
        group = new Group(name, dirPath, description);
        groups.append(group);

        success = qry.next();
    }//while database returns data

    return groups;
}

Highscores* Database::loadHighscores(){

    bool success = false;
    Highscores* highscores = new Highscores();
    Score* score = nullptr;
    User* user = nullptr;
    Group* group = nullptr;
    QSqlQuery qry;
    QString sqlBefehl;
    sqlBefehl = "SELECT User.username, Stereotype.name, Scoreboard.highscore "
                "FROM User, Stereotype, Scoreboard "
                "WHERE User.id = Scoreboard.id_user "
                "AND Stereotype.id = Scoreboard.id_stereotype";

    success = qry.exec(sqlBefehl);
    if(success){
        success = qry.first();
        while(success){
            user = new User(qry.value(0).toString(), "");
            group = new Group(qry.value(1).toString(), "", "");
            score = new Score(user, group, qry.value(2).toInt());
            highscores->addHighscore(score);
            success = qry.next();
        }//while success
    }//if success

    return highscores; //TODO
}

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
                                 "WHERE username = '" + user->getUsername()+ "'));";
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

/**
 * Shows the last error of the sqlExecution in the Console
 * @brief Datenbank::printError
 * @param qry
 */
void Database::printError(QSqlQuery qry){
    qDebug()<<qry.lastError().text(); //SQL-Fehler anzeigen
}
