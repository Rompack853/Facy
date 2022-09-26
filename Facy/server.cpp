#include "server.h"

/**
 * Construnctor
 * @brief Server::Server
 * @param parent
 * @param port
 */
Server::Server(QObject* parent, int port) : QObject(parent){

    this->port = port;  //setzte Port
    server = new QTcpServer(parent);    //erzeuge Server-Socket
    connect(server, SIGNAL(newConnection()), this, SLOT(buildConnection())); //verbinde newConnection des QTcpSockets mit buildConnection() dieser Klasse
    server->listen(QHostAddress::Any, port); //konfiguriere ip-adressen & empfangs-port fuer listener
    signalMapper = new QSignalMapper(this); //erzeuge Signalmapper
    connect(signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(recieve(QObject*))); //verbinde mapped()-methode des SignalMappers mit recieve() dieser Klasse
}

/**
 * Destructor
 * @brief Server::~Server
 */
Server::~Server(){
    sendBoradcast("CLOSED");
    for(Connection* c: connections){
        c->getSocket()->close();
        delete c;
    }//for c in connections
    connections.clear();
    server->close();
}//destuctor

//============SLOTS================0

/**
 * Tries to connect to an unknown amount of clients. Mybe 0 or more.
 * @brief Server::buildConnection
 */
void Server::buildConnection(){
    qDebug() << "[Server] building connection...";

    QTcpSocket* client = server->nextPendingConnection();
    QString randomID = "";

    if(client){
        randomID = Connection::generateRandomID();
        connections.append(new Connection(randomID, client));
        connect(client, SIGNAL(readyRead()), signalMapper, SLOT(map()));
        signalMapper->setMapping(client, client);

        send(client, "setID_" + randomID); //SENDS THE NEW GENERATED ID TO THE CLIENT
    }//if
}//buildConnection()

/**
 * recieves an Object of any Kind and tries to process it
 * @brief Server::recieve
 * @param client
 */
void Server::recieve(QObject* client){

    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(client);
    Connection* tmpConnection = searchConnection(socket);
    QString input = socket->readAll();

    qDebug() << "[Server] recieved from ["+ tmpConnection->getID() +"]: " + input;

    //TODO Implement Actions that should happen on specific messages

}//recieve()

//==============SLOTS==============end

/**
 * returns the whole Connection a specific socket
 * @brief Server::searchConnection
 * @param socket
 * @return
 */
Connection* Server::searchConnection(QTcpSocket* socket){
    qDebug() << "[Server] searching connection";
    Connection* tmpConnection = 0; //creates temporary Connection
    for(Connection* c: connections){
        if(c->getSocket() == socket){
            tmpConnection = c; //cache connection
            break;
        }//if sockets are identical
    }//for c in connections
    return tmpConnection;

}//searchConnection()

/**
 * sends a Message to a specified TcpSocket
 * @brief Server::send
 * @param socket
 * @param message
 */
void Server::send(QTcpSocket* socket, QString message){
    qDebug() << "[Server] sending to ["+ searchConnection(socket)->getID() +"]: " + message;
    socket->write(message.toLatin1());
}//send()

/**
 * sends a Unicast to a Connections specified by the recievers ID
 * @brief Server::sendUnicast
 * @param recieverID
 * @param message
 */
void Server::sendUnicast(QString recieverID, QString message){
    qDebug() << "[Server] sending to " + recieverID + ": " + message;
    for(Connection* c: connections){
        if(c->getID() == recieverID){
            c->getSocket()->write(message.toLatin1());
        }//if
    }//for
}//sendUnicast()

/**
 * Sends a Multicast to a List of Connections
 * @brief Server::sendMulticast
 * @param recieverIDs
 * @param message
 */
void Server::sendMulticast(QList<QString> recieverIDs, QString message){
   for(Connection* c: connections){
       for(QString id: recieverIDs){
           if(c->getID() == id){
               qDebug() << "[Server] sending to " + id + ": " + message;
               c->getSocket()->write(message.toLatin1());
           }//if IDs match
       }//for id in recieverIDs
   }//for c in connections
}//sendMulticast()

/**
 * Sends a Message to all current Connections
 * @brief Server::sendBoradcast
 * @param message
 */
void Server::sendBoradcast(QString message){
    qDebug() << "[Server] sending (Broadcast): " + message;
    for(Connection* c: connections){
        c->getSocket()->write(message.toLatin1());
    }
}//sendBroadcast()

/**
 * disconnects a Connection (specified by the TcpSocket) from the server
 * @brief Server::unsubscribe
 * @param socket
 */
void Server::unsubscribe(QTcpSocket* socket){

    qDebug() << "[Server] unsubscribing socket...";

    for(Connection* c: connections){
        if(c->getSocket() == socket){
            socket->close();
            connections.removeAll(c);
            delete socket;
        }//if
    }//for
}
