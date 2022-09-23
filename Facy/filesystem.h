#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QFile>
#include <QDir>

class Filesystem
{
public:
    static Filesystem* getInstance();
    bool createNewGroupDir(QString groupName);
    QString getFullPathOfDir(QString dirName);
private:

    Filesystem();
    bool mkDir(QString dirPath);
    bool rmDir(QString dirPath);

    QDir dir;
};

#endif // FILESYSTEM_H
