#include "admin.h"

//#########################
//VOLLSTAENDIG FERTIG
//#########################

Admin::Admin(QString username, QString secret) : User(username, secret)
{

}

QString Admin::getUsername(){

    return username;
}
