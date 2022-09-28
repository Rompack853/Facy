#ifndef SERVER_H
#define SERVER_H
#include <QWidget>
#include "connection.h"
#include "controller.h"

#include <QTcpServer>
#include <QSslKey>
#include <QSslCertificate>

class Server : public QTcpServer
{
    Q_OBJECT

public:

    Server(QObject *parent=0, int port=8080);
    ~Server();

private slots:

    void buildConnection();
    void recieve(QObject* client);
    void sslErrors(QList<QSslError> errors);
    //void disconnected();

private:

    Controller controller;
    //=======CONNECTION======
    int port; //the port clients will connect to
    QList<Connection*> connections;
    QSignalMapper* signalMapper;
    //=======CONNECTION======
    //=======DATA-FLOW=======
    QByteArray byteArr;
    QDataStream* writer;
    //=======SECURITY========
    QSslKey key;
    QSslCertificate cert;
    //=======SECURITY========

    Connection* searchConnection(QTcpSocket* socket);   //FERTIG
    QList<QString> splitAtTilde(QString str);           //FERTIG

    //TODO Maybe you need to replace QString message with an Object later
    void send(QTcpSocket* socket, QString message);                 //FERTIG
    void sendUnicast(QString recieverID, QString message);          //FERTIG
    void sendMulticast(QList<QString> recieverIDs, QString message);//FERTIG
    void sendBoradcast(QString message);                            //FERTIG
    void unsubscribe(QSslSocket* socket);

    //========Controller-Get=========
    void getGroups(QTcpSocket*, QString);       //TODO
    void getHighscores(QTcpSocket*, QString);   //TODO
    //========Server-Map=============
    void getGroupImages(QTcpSocket*, QString);  //TODO
    void createGroup(QTcpSocket*, QString);     //FERTIG
    void createAdmin(QTcpSocket*, QString);     //FERTIG
    void createUser(QTcpSocket*, QString);      //FERTIG
    void addHighscore(QTcpSocket*, QString);    //FERTIG
    //========Game-Logic=============
    void guessName(QTcpSocket*, QString);       //TODO
    //========Authentication=========
    void authenticateUser(QTcpSocket*, QString);//FERTIG
    //========Controller-Set=========


protected:
    void incomingConnection(qintptr socketDescriptor); //FERTIG
};

#endif // SERVER_H
