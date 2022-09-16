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

    QString getUsername();
    QString getSecret();

protected:
    QString username;
    QString secret;
};

#endif // USER_H
