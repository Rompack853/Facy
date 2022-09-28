#ifndef GROUP_H
#define GROUP_H

#include <QWidget>

class Group
{
public:
    Group(QString name, QString description=""); //An instance of the Group class represents a group of people

    QString getName();
    QString getDescription();
private:
    QString name;           //name of the Group
    QString description;    //some kind of short information about the group
};

#endif // GROUP_H
