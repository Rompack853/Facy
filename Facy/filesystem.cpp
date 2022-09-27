#include "filesystem.h"
#include <QDebug>

Filesystem::Filesystem()
{

}

/**
 * returns Singleton instance
 * @brief Filesystem::getInstance
 * @return
 */
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

    return mkDir("../resource/groups/"+groupName.toLower());
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

/**
 * Checks if a path refers to a File
 * @brief Filesystem::isFile
 * @param path
 * @return
 */
bool Filesystem::isFile(QString path){
    return QFile::exists(path);
}

/**
 * Removes a directory specified by the 'path' Parameter
 * @brief Filesystem::rmDir
 * @param dirPath
 * @return
 */
bool Filesystem::rmDir(QString dirPath){

    bool success = dir.rmdir(dirPath+"/");

    if( success )
        qDebug() << "Directory was deleted at: " << dirPath;
    else
        qDebug()<< "Directory couldn't be deleted at: " << dirPath;

    return success;
}

/**
 * Returns a List of all images in the directory of the specified 'group' Parameter
 * @brief Filesystem::loadImages
 * @param group
 * @return
 */
QList<QImage> Filesystem::loadImages(Group group){

    QImage* image;

    if(dir.cd("../resource/groups/" + group.getName().toLower())){
        for(QString entry: dir.entryList(QDir::Files, QDir::SortFlag::NoSort)){
            image->load(entry);
        }
    }


}//loadImages()
