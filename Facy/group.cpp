#include "group.h"

Group::Group(QString name, QString description)
{

    this->name = name;
    this->description = description;
}

QString Group::getName(){
    return this->name;
}

QString Group::getDescription(){
    return this->description;
}
