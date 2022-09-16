#include "admin.h"

Admin::Admin(QString username, QString secret) : User(username, secret)
{

}

QString Admin::getUsername(){

    return username;
}
