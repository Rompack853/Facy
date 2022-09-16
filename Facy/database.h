#ifndef DATABASE_H
#define DATABASE_H


class Database
{
public:
    Database();

    bool verbindungAufbauen();
    void verbindungSchliessen();
    void ausfuehren();
};

#endif // DATABASE_H
