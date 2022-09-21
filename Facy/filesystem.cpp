#include "filesystem.h"
#include <QDebug>

Filesystem::Filesystem()
{

}

Filesystem* Filesystem::getInstance(){
    static Filesystem* instance = nullptr;

    if(!instance){
        instance = new Filesystem();
    }
    return instance;
}

/**
 * Creates a directory for a new Group
 * @brief Filesystem::createNewGroupDir
 * @param groupName
 * @return
 */
bool Filesystem::createNewGroupDir(QString groupName){

    return mkDir("../resouce/groups/"+groupName.toLower());
}

/**
 * Creates a directory in the specified path
 * @brief Filesystem::mkDir
 * @param dirName
 * @return
 */
bool Filesystem::mkDir(QString dirPath){

    bool success = dir.mkdir(dirPath+"/");

    if( success )
        qDebug() << "Directory was created at: " << dirPath;
    else
        qDebug()<< "Directory couldn't be created at: " << dirPath;

    return success;
}

bool Filesystem::rmDir(QString dirPath){

    bool success = dir.rmdir(dirPath+"/");

    if( success )
        qDebug() << "Directory was deleted at: " << dirPath;
    else
        qDebug()<< "Directory couldn't be deleted at: " << dirPath;

    return success;
}
