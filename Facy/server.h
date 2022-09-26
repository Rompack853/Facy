#ifndef SERVER_H
#define SERVER_H
#include <QWidget>
#include "connection.h"

class Server : public QObject
{
    Q_OBJECT

public:

    Server(QObject *parent=0, int port=1001);
    ~Server();

private slots:

    void buildConnection();
    void recieve(QObject* client);

private:

    QTcpServer* server;
    int port;
    QList<Connection*> connections;
    QSignalMapper* signalMapper;

    Connection* searchConnection(QTcpSocket* socket);

    //TODO Maybe you need to replace QString message with an Object later
    void send(QTcpSocket* socket, QString message);
    void sendUnicast(QString recieverID, QString message);
    void sendMulticast(QList<QString> recieverIDs, QString message);
    void sendBoradcast(QString message);
    void unsubscribe(QTcpSocket* socket);
};

#endif // SERVER_H
