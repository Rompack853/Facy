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

    //QTcpServer* server;
    int port;
    QList<Connection*> connections;
    QSignalMapper* signalMapper;

    QSslKey key;
    QSslCertificate cert;

    Connection* searchConnection(QTcpSocket* socket);

    //TODO Maybe you need to replace QString message with an Object later
    void send(QTcpSocket* socket, QString message);
    void sendUnicast(QString recieverID, QString message);
    void sendMulticast(QList<QString> recieverIDs, QString message);
    void sendBoradcast(QString message);
    void unsubscribe(QSslSocket* socket);

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
