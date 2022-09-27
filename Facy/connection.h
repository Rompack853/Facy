#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
class Connection
{
public:
    Connection(QString id, QTcpSocket* socket);

    QString getID();
    bool isLoggedIn();
    QTcpSocket* getSocket();

    //void setID(int);
    void setLoggedIn(bool);

    static QString generateRandomID();

private:

    QString id;
    bool loggedIn;
    QTcpSocket* socket;

};

#endif // CONNECTION_H
