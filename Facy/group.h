#ifndef GROUP_H
#define GROUP_H

#include <QWidget>

class Group
{
public:
    Group(QString name, QString dirPath, QString description=""); //An instance of the Group class represents a group of people

    QString getName();
    QString getDescription();
    QString getDirPath();
private:
    QString name;           //name of the Group
    QString description;    //some kind of short information about the group
    QString dirPath;        //the path to the directory in which the Images of the groups related people are stored
};

#endif // GROUP_H
