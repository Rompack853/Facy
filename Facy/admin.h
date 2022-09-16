#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"


class Admin : public User
{
public:
    Admin(QString username, QString secret);
    virtual QString getUsername();
};

#endif // ADMIN_H
