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
 * Should convert an image into a format that can be sent through the Network
 * source: https://forum.qt.io/topic/92641/converting-a-qimage-to-a-qbytearray-and-convert-it-back-into-an-image
 * @brief Filesystem::toByteArray
 * @param image
 * @return
 */
QByteArray Filesystem::toByteArray(QImage* image){
    //Test & replace with solution
    return QByteArray::fromRawData((const char*)image->bits(), image->sizeInBytes());
}

/**
 * Creates a directory for a new Group
 * @brief Filesystem::createNewGroupDir
 * @param groupName
 * @return
 */
bool Filesystem::createNewGroupDir(QString groupName){

    return mkDir(pathGroupDir+groupName.toLower());
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
QList<QImage*> Filesystem::loadImages(Group* group){

    QList<QImage*> images;
    QImage* image;
    QString path = pathGroupDir + group->getName().toLower();

    if(dir.cd(path)){
        for(QString entry: dir.entryList(QDir::Files, QDir::SortFlag::NoSort)){
            image = new QImage(entry);
            image->load(path+"/"+entry);
            images.append(image);
        }//for
    }//if
    return images;
}//loadImages()
