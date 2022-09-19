#include "group.h"

Group::Group(QString name, QString dirPath, QString description)
{

    this->name = name;
    this->dirPath = dirPath;
    this->description = description;
}

QString Group::getName(){
    return this->name;
}

QString Group::getDirPath(){
    return this->dirPath;
}

QString Group::getDescription(){
    return this->description;
}
