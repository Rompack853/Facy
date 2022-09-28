#ifndef USER_H
#define USER_H
#include <QWidget>

class User
{
public:
    //keep secret encrypted 24/7 and just unencrypt when needed.
    User(QString username, QString secret);

    void setUsername(QString newUsername);
    void setSecret(QString newSecret);

    bool validateCredentials(QString tryUsername, QString trySecret);

    virtual QString getUsername();
    QString getSecret();

protected:
    QString username;
    QString secret;
};

#endif // USER_H
