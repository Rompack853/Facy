#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QFile>
#include <QDir>
#include "group.h"

class Filesystem
{
public:
    static Filesystem* getInstance();

    static QByteArray toByteArray(QImage);

    bool createNewGroupDir(QString groupName);
    QString getFullPathOfDir(QString dirName);
private:

    Filesystem();
    bool mkDir(QString dirPath);
    bool rmDir(QString dirPath);

    bool isDir(QString path);
    bool isFile(QString path);

    QList<QImage> loadImages(Group);
    QDir dir;
    //https://forum.qt.io/topic/50129/how-to-iterate-all-sub-folders-of-a-directory/4
};

#endif // FILESYSTEM_H
