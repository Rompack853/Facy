#ifndef GROUP_H
#define GROUP_H

#include <QWidget>

class Group
{
public:
    Group(QString name, QString dirPath, QString description="");

    QString getName();
    QString getDescription();
    QString getDirPath();
private:
    QString name;
    QString description;
    QString dirPath;
};

#endif // GROUP_H
