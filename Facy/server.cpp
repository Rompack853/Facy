#include "server.h"

#include <QSslSocket>
#include <QFile>

/*
 * Attention: Not all of the Code in this Class was written by the Team:
 * Encryption with QSslSocket has been inspired by:
 * https://github.com/jbagg/QSslSocket-example
 * */

/**
 * Construnctor
 * @brief Server::Server
 * @param parent
 * @param port
 */
Server::Server(QObject* parent, int port) : QTcpServer(parent){

    //loading the RSA-Private Key
    QFile keyFile("../Encryption/red_local.key");
    keyFile.open(QIODevice::ReadOnly);
    key = QSslKey(keyFile.readAll(), QSsl::Rsa);
    keyFile.close();

    //loading the Certificate
    QFile certFile("../Encryption/red_local.pem");
    certFile.open(QIODevice::ReadOnly);
    cert = QSslCertificate(certFile.readAll());
    certFile.close();

    /*if (!listen(QHostAddress("127.0.0.1"), port)) {
        qCritical() << "Unable to start the TCP server";
        exit(0);
    }*/

    //writer = new QDataStream(&byteArr, QIODevice::WriteOnly);
    this->port = port;  //setzte Port

    connect(this, SIGNAL(newConnection()), this, SLOT(buildConnection())); //verbinde newConnection des QTcpSockets mit buildConnection() dieser Klasse
    this->listen(QHostAddress::Any, port); //konfiguriere ip-adressen & empfangs-port fuer listener
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
    this->close();
}//destuctor

//============SLOTS================0

/**
 * Tries to connect to an unknown amount of clients. Mybe 0 or more.
 * @brief Server::buildConnection
 */
void Server::buildConnection(){
    qDebug() << "[Server] building connection...";

    QTcpSocket* client = this->nextPendingConnection();
    QString randomID = "";

    //connect(client, SIGNAL(readyRead()), this, SLOT(recieve()));

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

    if(input.indexOf("GET_GROUPS")==0) {
        getGroups(socket, input);
    } else if(input.indexOf("GET_HIGHSCORES")==0) {
        getHighscores(socket, input);
    } else if(input.indexOf("GET_GROUP_IMAGES~")==0) {
        getGroupImages(socket, input);
    } else if(input.indexOf("CREATE_GROUP~")==0) {
        createGroup(socket, input);
    } else if(input.indexOf("CREATE_HIGHSCORE~")==0){
        addHighscore(socket, input);
    } else if(input.indexOf("CREATE_USER~")==0) {
        createUser(socket, input);
    } else if(input.indexOf("CREATE_ADMIN~")==0) {
        createAdmin(socket, input);
    } else if(input.indexOf("GUESS_NAME~")==0){
        //TODO
    } else if(input.indexOf("LOGIN~")==0){
        authenticateUser(socket, input);
    }

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
void Server::unsubscribe(QSslSocket* socket){

    qDebug() << "[Server] unsubscribing socket...";

    for(Connection* c: connections){
        if(c->getSocket() == socket){
            socket->close();
            connections.removeAll(c);
            delete c->getSocket();
        }//if
    }//for
}

/**
 * @brief Server::incomingConnection
 * @param socketDescriptor
 */
void Server::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket *sslSocket = new QSslSocket(this);

    connect(sslSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
    sslSocket->setSocketDescriptor(socketDescriptor);
    //sslSocket->setPrivateKey(key);
    //sslSocket->setLocalCertificate(cert);

    //See 'Configuring QSslSocket' on: https://doc.qt.io/qt-6/network-changes-qt6.html
    auto sslConfiguration = QSslConfiguration::defaultConfiguration();
    sslConfiguration.setPrivateKey(key);
    sslConfiguration.setLocalCertificate(cert);
    sslConfiguration.addCaCertificates("../Encryption/blue_ca.pem");
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyPeer);
    sslSocket->setSslConfiguration(sslConfiguration);

    //sslSocket->addCaCertificates("../Encryption/blue_ca.pem");
    //sslSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);
    sslSocket->startServerEncryption();

    addPendingConnection(sslSocket);
}

/**
 * Prints error String to console
 * @brief Server::sslErrors
 * @param errors
 */
void Server::sslErrors(QList<QSslError> errors){
    for(QSslError error: errors){
        qDebug() << error.errorString();
    }//for
}

//===================SERVER-Map==========================
void Server::getGroupImages(QTcpSocket* socket, QString input){

    //will get the group name specified after '~'
    QString groupname = input.mid(input.indexOf("~")+1, input.length());

    //loads the images from the filesystem of the group
    //specified in the groupname
    for(QImage* img: Filesystem::getInstance()->loadImages(controller.getGroupByName(groupname))){
        //send each image converted as Bytearray to the Client
        if(socket->write(Filesystem::toByteArray(img)) == -1){
            qDebug() << "Error while sending image";
        }//if
    }//for
    //inform the Client that all images have been send
    send(socket, "IMGS_END");
}//getGroupImages();

void Server::getGroups(QTcpSocket* socket, QString input){

    for(Group* g: controller.getGroups()){
        g->getName();
    }//for

}//getGroups()

void Server::getHighscores(QTcpSocket* socket, QString input){

}//getHighscores()

/**
 * Adds a Group to the Game, if possible
 * @brief Server::createGroup
 * @param socket
 * @param input
 */
void Server::createGroup(QTcpSocket* socket, QString input){
    QList<QString> result = splitAtTilde(input);
    if(!controller.addGroup(result.at(0), result.at(1))){
        socket->write("CREATE_GROUP_FAILED");
    }//if something went wrong while creating the Group
}//createGroup()

/**
 * Adds an Admin to the Game if possible
 * @brief Server::createAdmin
 * @param socket
 * @param input
 */
void Server::createAdmin(QTcpSocket* socket, QString input){
    QList<QString> result = splitAtTilde(input);
    if(!controller.addUser(Role::ADMIN, result.at(0), result.at(1))){
        socket->write("CREATE_USER_FAILED");
    }//if something went wrong while creating the Admin
}//createAdmin()

/**
 * Adds an User to the Game if possible
 * @brief Server::createUser
 * @param socket
 * @param input
 */
void Server::createUser(QTcpSocket* socket, QString input){
    QList<QString> result = splitAtTilde(input);
    if(!controller.addUser(Role::USER, result.at(0), result.at(1))){
        socket->write("CREATE_USER_FAILED");
    }//if something went wrong while creating the User
}//createUser()

/**
 * Adds an Highscore to the Game if possible
 * @brief Server::addHighscore
 * @param socket
 * @param input
 */
void Server::addHighscore(QTcpSocket* socket, QString input){
    QList<QString> result = splitAtTilde(input);
    if(!controller.addHighscore(result.at(0), result.at(1), result.at(2).toInt())){
        socket->write("CREATE_HIGHSCORE_FAILED");
    }//if something went wrong while creating the Highscore
}//addHighscore()

void Server::guessName(QTcpSocket* socket, QString input){
    //TODO
}//guessName()

void Server::authenticateUser(QTcpSocket* socket, QString input){
    QList<QString> result = splitAtTilde(input);
    for(User* user: controller.getUsers()){
        if(user->validateCredentials(result.at(0), result.at(1))){
            if(dynamic_cast<Admin*>(user) != nullptr){
                socket->write("LOGIN_CORRECT~admin");
            } else {
                socket->write("LOGIN_CORRECT~user");
            }
            return;
        }//if user-credentials are correct
    }//for user in users
    socket->write("LOGIN_FAILED");
}//authenticate()

//=======MISC========
QList<QString> Server::splitAtTilde(QString str){

    QList<QString> strings;
    int index;

    while(str.contains("~")){
        str = str.remove(0, str.indexOf("~")+1); //remove first part of string including the first ~
        index = str.indexOf("~");
        if(index >= 0)
            strings.append(str.mid(0, index)); //stores the part of the String
        else{
            strings.append(str.mid(0, str.length()));
            return strings;
        }//else
    }//while
    return strings;
}//splitAtTilde()
